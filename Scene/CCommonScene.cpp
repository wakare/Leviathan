#include <fstream>
#include <string>
#include <GL\glew.h>
#include <sstream>
#include "CCommonScene.h"
#include "DynamicArray.h"
#include "CFileImportFactory.h"
#include "GeometryCalculator.h"
#include "DrawableNode.h"
#include "SOIL.h"
#include "PictureObject.h"

namespace Leviathan
{
	CCommonScene::CCommonScene(GLFWwindow* pRenderWindow, int width, int height) :
		IScene(),
		m_pGLFWWindow(pRenderWindow), 
		m_pRenderWarpper(nullptr), 
		m_pMeshPass(nullptr), 
		m_pShaderProgram(nullptr),
		m_pSceneGraph(nullptr)
	{
		m_pRenderWarpper = new RenderWrapper(pRenderWindow);

		if (!m_pRenderWarpper)
		{
			LeviathanOutStream << "[FATAL] RenderWrapper init failed." << std::endl;
			throw "RenderWrapper init failed.";
			return;
		}

		if (!_initCamera(width, height))
		{
			LeviathanOutStream << "[FATAL] Scene camera init failed." << std::endl;
			throw "Scene camera init failed.";
			return;
		}

		const char* pczVertexShaderPath = "ShaderSource\\VertexShader.glsl";
		const char* pczFragmentShaderPath = "ShaderSource\\FragmentShader.glsl";
		if (!_initShaderSource(pczVertexShaderPath, pczFragmentShaderPath))
		{
			LeviathanOutStream << "[FATAL] Scene ShaderSource init failed." << std::endl;
			throw "Scene ShaderSource init failed.";
			return;
		}

		m_pMeshPass = new TriDObjectGLPass(m_pShaderProgram, m_pCamera);
		if (!m_pMeshPass)
		{
			return;
		}
		//m_pMeshPass->SetCullFace(GL_CCW);

		m_pSceneGraph = new SceneGraph(TryCast<TriDObjectGLPass, GLPass>(m_pMeshPass));
		m_pRenderWarpper->AddGLPass(TryCast<TriDObjectGLPass, GLPass>(m_pMeshPass));
	};

	bool CCommonScene::_initSceneObject()
	{
		if (!_initLight())
		{
			LeviathanOutStream << "[ERROR] Init light failed." << std::endl;
			return false;
		}

		float cubeAABB[6] =
		{
			10.0f, 10.0f, 10.0f,
			20.0f, 20.0f, 20.0f,
		};

		LPtr<GLObject> pCubeGLObject = _convertAABBtoGLObject(cubeAABB);
		pCubeGLObject->SetLightEnable(true);
		LPtr<GLCommonMaterial> pMaterial = new GLCommonMaterial({ 0.5f, 0.5f, 0.5f }, { 0.8f, 0.8f, 0.8f }, {1.0f, 1.0f, 1.0f});

		// Load file as texture 
		PictureObject texture("container.jpg");

		pMaterial->AddTexture2D(new GLTexture2D(texture.m_pData, texture.m_nWidth, texture.m_nHeight));
		pCubeGLObject->SetMaterial(TryCast<GLCommonMaterial, IGLMaterial>(pMaterial));

		LPtr<DrawableNode<SceneNode>> pCubeNode = new DrawableNode<SceneNode>(pCubeGLObject, new SceneNode());
		m_pSceneGraph->AddNode(TryCast<DrawableNode<SceneNode>, Node<SceneNode>>(pCubeNode), true);
		m_pCamera->LookAt({ 15.0f, 15.0f, 15.0f });

		auto pSceneNode = LPtr<SceneNode>(new SceneNode());
		pSceneNode->LoadModelFile("dental.stl");
		pSceneNode->SetWorldCoord(Vector3f(-100.0f, 100.0f, 10.0f));
		LPtr<DrawableNode<SceneNode>> pDentalNode = new DrawableNode<SceneNode>(pSceneNode->GetModelFile(), pSceneNode);

		auto& AABB = pSceneNode->GetModelFile()->GetAABB();
		float RenderObjectAABBCenter[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
		if (!AABB.GetAABBCenter(RenderObjectAABBCenter))
		{
			LeviathanOutStream << "[ERROR] Get AABB failed." << std::endl;
			return false;
		}

		auto pDentalGLObject = pDentalNode->GetGLObject();
		auto pNode = TryCast<DrawableNode<SceneNode>, Node<SceneNode>>(pDentalNode);
		m_pSceneGraph->AddNode(pNode, true);

		LPtr<IGLMaterial> pModelMaterial = new GLCommonMaterial({ 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f });
		pDentalGLObject->SetMaterial(pModelMaterial);
		pDentalGLObject->SetLightEnable(true);

		// Set camera lookAt
		m_pCamera->LookAt(Vector4f(RenderObjectAABBCenter) * pDentalNode->GetNodeData()->GetWorldTransform(), AABB.GetAABBRadius() * 2.0f);
		pDentalGLObject->SetModelMatrix(pDentalNode->GetNodeData()->GetWorldTransform().GetInverseMatrix());

		return true;
	}

	bool CCommonScene::_initShaderSource(const char* pczVertexShaderPath, const char* pczFragmentShaderPath)
	{
		auto strVertexShader = _getShaderSource(pczVertexShaderPath);
		auto strFragmentShader = _getShaderSource(pczFragmentShaderPath);

		const char* pczVertexShaderSource = strVertexShader.c_str();
		const char* pczFragmentShaderSource = strFragmentShader.c_str();

		m_pShaderProgram = new GLShaderProgram(&pczVertexShaderSource, &pczFragmentShaderSource, nullptr);
		if (!m_pShaderProgram)
		{
			return false;
		}

		if (!m_pShaderProgram->Init())
		{
			return false;
		}

		return true;
	}

	bool CCommonScene::_initCamera(unsigned uWidth, unsigned uHeight)
	{
		float cameraEye[3] = { 0.0f, 0.0f, -10.0f };
		float cameraLookAt[3] = { 0.0f, 0.0f, 0.0f };
		float cameraUp[3] = { 0.0f, 1.0f, 0.0f };

		float fovy = PI_FLOAT * (45.0f / 180.0f);
		float fAspect = (1.0f * uWidth) / uHeight;
		float fNear = 0.01f;
		float fFar = 1000.0f;

		m_pCamera = new GLCamera(cameraEye, cameraLookAt, cameraUp, fovy, fAspect, fNear, fFar);
		if (!m_pCamera)
		{
			throw "Exception";
			return false;
		}

		return true;
	}

	bool CCommonScene::_initLight()
	{
		LPtr<GLLight> light = new GLLight({ -100.0f, 100.0f, 10.0f }, { 0.5f, 0.5f, 0.5f }, { 0.8f, 0.8f, 0.8f }, { 1.0f, 1.0f, 1.0f });
		m_pMeshPass->AddGLLight(light);
		m_pLights.push_back(light);
		
		return true;
	}

	CCommonScene::~CCommonScene()
	{

	}

	void CCommonScene::Update()
	{
		static bool bFirstUpdate = true;
		if (bFirstUpdate)
		{
			if (!_initSceneObject())
			{
				LeviathanOutStream << "[ERROR] Init scene object failed." << std::endl;
			}

			bFirstUpdate = false;
		}

		m_pRenderWarpper->Render();
	}

	std::string CCommonScene::_getShaderSource(const char* pczShaderSourcePath)
	{
		std::ifstream shaderSourceFileStream(pczShaderSourcePath, std::ios::in);
		if (!shaderSourceFileStream.is_open())
		{
			throw "std::string Scene::_getShaderSource(const char* pczShaderSourcePath) --> Invalid ShaderSource paths.";
			return std::string();
		}

		std::stringstream strStream;
		strStream << shaderSourceFileStream.rdbuf();

		return strStream.str();
	}

	Leviathan::LPtr<Leviathan::GLObject> CCommonScene::_convertModelFileToGLObject(LPtr<IModelStruct> modelFile)
	{
		const unsigned uVertexFloatCount = 10;

		DynamicArray<float> glData(modelFile->GetTriangleCount() * 3 * uVertexFloatCount * sizeof(float));
		
		static float defaultColor[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
		bool bDefaultColor = false;
		
		auto color = modelFile->GetVertexColorArray();
		if (!color)
		{
			bDefaultColor = true;
		}

		for (unsigned i = 0; i < modelFile->GetTriangleCount(); i++)
		{
			unsigned* vertexIndex = modelFile->GetTriangleIndexArray() + 3 * i;
			float* vertices[3];

			for (unsigned j = 0; j < 3; j++)
			{
				float* vertexCoord = modelFile->GetVertex3DCoordArray() + 3 * vertexIndex[j];
				vertices[j] = vertexCoord;
				memcpy(glData.m_pData + 3 * uVertexFloatCount * i + uVertexFloatCount * j, vertexCoord, sizeof(float) * 3);
				
				if (bDefaultColor)
				{
					memcpy(glData.m_pData + 3 * uVertexFloatCount * i + uVertexFloatCount * j + 3, defaultColor, sizeof(float) * 4);
				}
				else
				{
					memcpy(glData.m_pData + 3 * uVertexFloatCount * i + uVertexFloatCount * j + 3, color + 4 * i, sizeof(float) * 4);
				}
			}

			float fNormal[3];
			GeometryCalculator::CalNormal(vertices[0], vertices[1], vertices[2], fNormal);

			for (unsigned j = 0; j < 3; j++)
			{
				memcpy(glData.m_pData + 3 * uVertexFloatCount * i + uVertexFloatCount * j + 7, fNormal, sizeof(float) * 3);
			}
		}

		return new TriDGLObject(GL_TRIANGLES, glData.m_pData, modelFile->GetTriangleCount() * 3, TriDGLObject::VERTEX_ATTRIBUTE_XYZ | TriDGLObject::VERTEX_ATTRIBUTE_RGBA | TriDGLObject::VERTEX_ATTRIBUTE_NXYZ);
	}

	Leviathan::LPtr<Leviathan::GLObject> CCommonScene::_convertAABBtoGLObject(const AABB& aabb)
	{
		float fRadius = aabb.GetAABBRadius();
		if (fRadius < 0.0f)
		{
			LeviathanOutStream << "[ERROR] AABB radius less than zero." << std::endl;
			return nullptr;
		}

		constexpr int nVertexFloatCount = 12;

// 		float cube[36 * nVertexFloatCount] =
// 		{
// 			// front						// color			 // normal			// texCoord
// 			-fRadius, -fRadius, -fRadius, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
// 			 fRadius, -fRadius, -fRadius, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
// 			 fRadius,  fRadius, -fRadius, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
// 			 fRadius,  fRadius, -fRadius, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
// 			-fRadius,  fRadius, -fRadius, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
// 			-fRadius, -fRadius, -fRadius, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
// 
// 			// up
// 			-fRadius, fRadius, -fRadius, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
// 			 fRadius, fRadius, -fRadius, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
// 			 fRadius, fRadius,  fRadius, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
// 			 fRadius, fRadius,  fRadius, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
// 			-fRadius, fRadius,  fRadius, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
// 			-fRadius, fRadius, -fRadius, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
// 
// 			// down
// 			-fRadius, -fRadius, -fRadius, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
// 			 fRadius, -fRadius,  fRadius, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
// 			 fRadius, -fRadius, -fRadius, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
// 			 fRadius, -fRadius,  fRadius, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
// 			-fRadius, -fRadius, -fRadius, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
// 			-fRadius, -fRadius,  fRadius, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
// 
// 			// left
// 			-fRadius, -fRadius, -fRadius, 1.0f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
// 			-fRadius,  fRadius, -fRadius, 0.0f, 1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
// 			-fRadius,  fRadius,  fRadius, 0.0f, 0.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
// 			-fRadius,  fRadius,  fRadius, 1.0f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
// 			-fRadius, -fRadius,  fRadius, 0.0f, 1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
// 			-fRadius, -fRadius, -fRadius, 0.0f, 0.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
// 
// 			// right
// 			fRadius, -fRadius, -fRadius, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
// 			fRadius,  fRadius,  fRadius, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
// 			fRadius,  fRadius, -fRadius, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
// 			fRadius,  fRadius,  fRadius, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
// 			fRadius, -fRadius, -fRadius, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
// 			fRadius, -fRadius,  fRadius, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
// 
// 			// back
// 			-fRadius, -fRadius, fRadius, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
// 			 fRadius,  fRadius, fRadius, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
// 			 fRadius, -fRadius, fRadius, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
// 			 fRadius,  fRadius, fRadius, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
// 			-fRadius, -fRadius, fRadius, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
// 			-fRadius,  fRadius, fRadius, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
// 		};
// 
// 		// Move to center
// 		float center[3];
// 		aabb.GetAABBCenter(center);
// 
// 		for (unsigned i = 0; i < 36; i++)
// 		{
// 			cube[nVertexFloatCount * i] += center[0];
// 			cube[nVertexFloatCount * i + 1] += center[1];
// 			cube[nVertexFloatCount * i + 2] += center[2];
// 		}

		float fNormalSubValue = sqrtf(1.0f / 3.0f);

		float vertices[8 * nVertexFloatCount] = 
		{
			-fRadius, -fRadius, -fRadius,  1.0f, 0.0f, 0.0f, 1.0f, -fNormalSubValue, -fNormalSubValue, -fNormalSubValue, 0.0f, 0.0f,
			 fRadius, -fRadius, -fRadius,  0.0f, 1.0f, 0.0f, 1.0f,  fNormalSubValue, -fNormalSubValue, -fNormalSubValue, 1.0f, 0.0f,
			 fRadius,  fRadius, -fRadius,  0.0f, 0.0f, 1.0f, 1.0f,  fNormalSubValue,  fNormalSubValue, -fNormalSubValue, 1.0f, 1.0f,
			-fRadius,  fRadius, -fRadius,  0.0f, 1.0f, 0.0f, 1.0f, -fNormalSubValue,  fNormalSubValue, -fNormalSubValue, 0.0f, 1.0f,
			-fRadius, -fRadius,  fRadius,  1.0f, 0.0f, 0.0f, 1.0f, -fNormalSubValue, -fNormalSubValue,  fNormalSubValue, 1.0f, 1.0f,
			 fRadius, -fRadius,  fRadius,  0.0f, 1.0f, 0.0f, 1.0f,  fNormalSubValue, -fNormalSubValue,  fNormalSubValue, 0.0f, 1.0f,
			 fRadius,  fRadius,  fRadius,  0.0f, 0.0f, 1.0f, 1.0f,  fNormalSubValue,  fNormalSubValue,  fNormalSubValue, 0.0f, 0.0f,
			-fRadius,  fRadius,  fRadius,  0.0f, 1.0f, 0.0f, 1.0f, -fNormalSubValue,  fNormalSubValue,  fNormalSubValue, 1.0f, 0.0f,
		};

		// Move to center
		float center[3];
		aabb.GetAABBCenter(center);

		for (unsigned i = 0; i < 8; i++)
		{
			vertices[nVertexFloatCount * i]		+= center[0];
			vertices[nVertexFloatCount * i + 1] += center[1];
			vertices[nVertexFloatCount * i + 2] += center[2];
		}

		constexpr unsigned uCubeTriangleCount = 36;
		unsigned vertexIndices[uCubeTriangleCount] = 
		{
			0, 1, 2, 
			0, 2, 3, 
			1, 5, 6, 
			1, 6, 2, 
			3, 2, 6, 
			3, 6, 7, 
			0, 7, 4, 
			0, 3, 7,
			0, 5, 1,
			0, 4, 5,
			4, 6, 5,
			4, 7, 6
		};

		//auto result = new TriDGLObject(GL_TRIANGLES, cube, 36, TriDGLObject::VERTEX_ATTRIBUTE_XYZ | TriDGLObject::VERTEX_ATTRIBUTE_RGBA | TriDGLObject::VERTEX_ATTRIBUTE_NXYZ | TriDGLObject::VERTEX_ATTRIBUTE_TEX);
		auto result = new TriDGLObject(GL_TRIANGLES, vertices, 8, TriDGLObject::VERTEX_ATTRIBUTE_XYZ | TriDGLObject::VERTEX_ATTRIBUTE_RGBA | TriDGLObject::VERTEX_ATTRIBUTE_NXYZ | TriDGLObject::VERTEX_ATTRIBUTE_TEX, nullptr, nullptr, vertexIndices, uCubeTriangleCount);
		return result;
	}

	Leviathan::LPtr<Leviathan::GLObject> CCommonScene::_getPointGLObject(float* pCoordData, unsigned uVertexCount, float *pColorData /*= nullptr*/)
	{
		static float defaultColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
		const int nVertexSize = 7;
		DynamicArray<float> pArray(uVertexCount * nVertexSize * sizeof(float));
		
		for (unsigned i = 0; i < uVertexCount; i++)
		{
			memcpy(pArray.m_pData + nVertexSize * i, pCoordData + 3 * i, sizeof(float) * 3);
			
			if (pColorData)
			{
				memcpy(pArray.m_pData + nVertexSize * i + 3, pColorData + 4 * i, sizeof(float) * 4);
			}
			else
			{
				memcpy(pArray.m_pData + nVertexSize * i + 3, defaultColor, sizeof(float) * 4);
			}
		}

		return new TriDGLObject(GL_POINTS, pArray.m_pData, uVertexCount, TriDGLObject::VERTEX_ATTRIBUTE_XYZ | TriDGLObject::VERTEX_ATTRIBUTE_RGBA);
	}
}