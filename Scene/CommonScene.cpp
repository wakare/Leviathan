#include <fstream>
#include <string>
#include <GL\glew.h>
#include <sstream>
#include "CommonScene.h"
#include "DynamicArray.h"
#include "CFileImportFactory.h"
#include "GeometryCalculator.h"
#include "DrawableNode.h"

namespace Leviathan
{
	CommonScene::CommonScene(GLFWwindow* pRenderWindow, int width, int height) :
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

		if (!InitCamera(width, height))
		{
			LeviathanOutStream << "[FATAL] Scene camera init failed." << std::endl;
			throw "Scene camera init failed.";
			return;
		}

		const char* pczVertexShaderPath = "ShaderSource\\VertexShader.glsl";
		const char* pczFragmentShaderPath = "ShaderSource\\FragmentShader.glsl";
		if (!InitShaderSource(pczVertexShaderPath, pczFragmentShaderPath))
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

		m_pSceneGraph = new SceneGraph(TryCast<TriDObjectGLPass, GLPass>(m_pMeshPass));
	};

	bool CommonScene::InitSceneObject()
	{
		float cubeAABB[6] =
		{
			10.0f, 10.0f, 10.0f,
			20.0f, 20.0f, 20.0f,
		};

		LPtr<GLObject> pCubeGLObject = _convertAABBtoGLObject(cubeAABB);
		pCubeGLObject->SetLightEnable(false);
		LPtr<DrawableNode<SceneNode>> pCubeNode = new DrawableNode<SceneNode>(pCubeGLObject, new SceneNode());
		m_pSceneGraph->AddNode(TryCast<DrawableNode<SceneNode>, Node<SceneNode>>(pCubeNode));

		auto pDentalFile = CFileImportFactory::GetFileImportFactory()->LoadFile("dental.stl");
		if (!pDentalFile)
		{
			LeviathanOutStream << "[ERROR] Load file failed." << std::endl;
			return false;
		}

		auto& AABB = pDentalFile->GetAABB();
		float RenderObjectAABBCenter[4];
		if (!AABB.GetAABBCenter(RenderObjectAABBCenter))
		{
			LeviathanOutStream << "[ERROR] Get AABB failed." << std::endl;
			return false;
		}

		// Set camera lookAt
		RenderObjectAABBCenter[3] = 1.0f;
		Vector4f modelCoord = RenderObjectAABBCenter;

		LPtr<Matrix4f> pModelMatrix = new Matrix4f();
		Matrix4f::GetTranslateMatrix(-100.0f, 100.0f, 10.0f, *pModelMatrix);
		Vector4f worldCoord = modelCoord * (*pModelMatrix);

		m_pCamera->m_fLookAt[0] = worldCoord.GetData()[0];
		m_pCamera->m_fLookAt[1] = worldCoord.GetData()[1];
		m_pCamera->m_fLookAt[2] = worldCoord.GetData()[2];

		LPtr<DrawableNode<SceneNode>> node = new DrawableNode<SceneNode>(pDentalFile, LPtr<SceneNode>(new SceneNode()));
		auto pDentalGLObject = node->GetGLObject();
		auto pNode = TryCast<DrawableNode<SceneNode>, Node<SceneNode>>(node);
		m_pSceneGraph->AddNode(pNode);

		LPtr<GLMaterial> pMaterial = new CommonGLMaterial({ 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f });
		pDentalGLObject->SetMaterial(pMaterial);
		pDentalGLObject->SetLightEnable(true);

		pModelMatrix->InverseSelf();
		pDentalGLObject->SetModelMatrix(pModelMatrix);

		memcpy(m_pCamera->m_fEye, m_pCamera->m_fLookAt, sizeof(float) * 3);
		m_pCamera->m_fEye[0] -= (AABB.GetAABBRadius() * 2);

		LPtr<GLLight> light = new GLLight({ 0.0f, 0.0f, 0.0f }, { 0.2f, 0.2f, 0.2f }, { 0.8f, 0.8f, 0.8f }, { 1.0f, 1.0f, 1.0f });

		m_pMeshPass->AddGLLight(light);
		m_pRenderWarpper->AddGLPass(TryCast<TriDObjectGLPass, GLPass>(m_pMeshPass));

		return true;
	}

	bool CommonScene::InitShaderSource(const char* pczVertexShaderPath, const char* pczFragmentShaderPath)
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

	bool CommonScene::InitCamera(unsigned uWidth, unsigned uHeight)
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

	CommonScene::~CommonScene()
	{

	}

	void CommonScene::Update()
	{
		static bool bFirstUpdate = true;
		if (bFirstUpdate)
		{
			if (!InitSceneObject())
			{
				LeviathanOutStream << "[ERROR] Init scene object failed." << std::endl;
			}

			bFirstUpdate = false;
		}

		m_pRenderWarpper->Render();
	}

	std::string CommonScene::_getShaderSource(const char* pczShaderSourcePath)
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

	Leviathan::LPtr<Leviathan::GLObject> CommonScene::_convertModelFileToGLObject(LPtr<IModelStruct> modelFile)
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

	Leviathan::LPtr<Leviathan::GLObject> CommonScene::_convertAABBtoGLObject(const AABB& aabb)
	{
		float fRadius = aabb.GetAABBRadius();
		if (fRadius < 0.0f)
		{
			LeviathanOutStream << "[ERROR] AABB radius less than zero." << std::endl;
			return nullptr;
		}

		float cube[252] =
		{
			// front			 // color
			-fRadius, -fRadius, -fRadius, 1.0f, 0.0f, 0.0f, 1.0f,
			fRadius, -fRadius, -fRadius, 0.0f, 1.0f, 0.0f, 1.0f,
			fRadius,  fRadius, -fRadius, 0.0f, 0.0f, 1.0f, 1.0f,
			fRadius,  fRadius, -fRadius, 1.0f, 0.0f, 0.0f, 1.0f,
			-fRadius,  fRadius, -fRadius, 0.0f, 1.0f, 0.0f, 1.0f,
			-fRadius, -fRadius, -fRadius, 0.0f, 0.0f, 1.0f, 1.0f,

			// up
			-fRadius, fRadius, -fRadius, 1.0f, 0.0f, 0.0f, 1.0f,
			fRadius, fRadius, -fRadius, 0.0f, 1.0f, 0.0f, 1.0f,
			fRadius, fRadius,  fRadius, 0.0f, 0.0f, 1.0f, 1.0f,
			fRadius, fRadius,  fRadius, 1.0f, 0.0f, 0.0f, 1.0f,
			-fRadius, fRadius,  fRadius, 0.0f, 1.0f, 0.0f, 1.0f,
			-fRadius, fRadius, -fRadius, 0.0f, 0.0f, 1.0f, 1.0f,

			// down
			-fRadius, -fRadius, -fRadius, 1.0f, 0.0f, 0.0f, 1.0f,
			fRadius, -fRadius, -fRadius, 0.0f, 1.0f, 0.0f, 1.0f,
			fRadius, -fRadius,  fRadius, 0.0f, 0.0f, 1.0f, 1.0f,
			fRadius, -fRadius,  fRadius, 1.0f, 0.0f, 0.0f, 1.0f,
			-fRadius, -fRadius,  fRadius, 0.0f, 1.0f, 0.0f, 1.0f,
			-fRadius, -fRadius, -fRadius, 0.0f, 0.0f, 1.0f, 1.0f,

			// left
			-fRadius, -fRadius, -fRadius, 1.0f, 0.0f, 0.0f, 1.0f,
			-fRadius,  fRadius, -fRadius, 0.0f, 1.0f, 0.0f, 1.0f,
			-fRadius,  fRadius,  fRadius, 0.0f, 0.0f, 1.0f, 1.0f,
			-fRadius,  fRadius,  fRadius, 1.0f, 0.0f, 0.0f, 1.0f,
			-fRadius, -fRadius,  fRadius, 0.0f, 1.0f, 0.0f, 1.0f,
			-fRadius, -fRadius, -fRadius, 0.0f, 0.0f, 1.0f, 1.0f,

			// right
			fRadius, -fRadius, -fRadius, 1.0f, 0.0f, 0.0f, 1.0f,
			fRadius,  fRadius, -fRadius, 0.0f, 1.0f, 0.0f, 1.0f,
			fRadius,  fRadius,  fRadius, 0.0f, 0.0f, 1.0f, 1.0f,
			fRadius,  fRadius,  fRadius, 1.0f, 0.0f, 0.0f, 1.0f,
			fRadius, -fRadius,  fRadius, 0.0f, 1.0f, 0.0f, 1.0f,
			fRadius, -fRadius, -fRadius, 0.0f, 0.0f, 1.0f, 1.0f,

			// back
			-fRadius, -fRadius, fRadius, 1.0f, 0.0f, 0.0f, 1.0f,
			fRadius, -fRadius, fRadius, 0.0f, 1.0f, 0.0f, 1.0f,
			fRadius,  fRadius, fRadius, 0.0f, 0.0f, 1.0f, 1.0f,
			fRadius,  fRadius, fRadius, 1.0f, 0.0f, 0.0f, 1.0f,
			-fRadius,  fRadius, fRadius, 0.0f, 1.0f, 0.0f, 1.0f,
			-fRadius, -fRadius, fRadius, 0.0f, 0.0f, 1.0f, 1.0f,
		};

		// Move to center
		float center[3];
		aabb.GetAABBCenter(center);

		for (unsigned i = 0; i < 36; i++)
		{
			cube[7 * i] += center[0];
			cube[7 * i + 1] += center[1];
			cube[7 * i + 2] += center[2];
		}

		auto result = new TriDGLObject(GL_TRIANGLES, cube, 36, TriDGLObject::VERTEX_ATTRIBUTE_XYZ | TriDGLObject::VERTEX_ATTRIBUTE_RGBA);
		return result;
	}

	Leviathan::LPtr<Leviathan::GLObject> CommonScene::_getPointGLObject(float* pCoordData, unsigned uVertexCount, float *pColorData /*= nullptr*/)
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