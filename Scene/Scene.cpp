#include "Scene.h"
#include <fstream>
#include <string>
#include <GL\glew.h>
#include <sstream>
#include "DynamicArray.h"
#include "..\FileImporter\CFileImportFactory.h"

namespace Leviathan
{
	Scene::Scene(GLFWwindow* pRenderWindow, int width, int height) :
		m_pCamera(nullptr), m_pGLFWWindow(pRenderWindow), m_pRenderWarpper(nullptr), m_pMeshPass(nullptr), m_pShaderProgram(nullptr)
	{
		m_pRenderWarpper = new RenderWrapper(pRenderWindow);
		if (!m_pRenderWarpper)
		{
			throw "RenderWrapper init failed.";
			return;
		}

		float cameraEye[3] = { 0.0f, 0.0f, -10.0f };
		float cameraLookAt[3] = { 0.0f, 0.0f, 0.0f };
		float cameraUp[3] = { 0.0f, 1.0f, 0.0f };

		float fovy = PI * (45.0f / 180.0f);
		float aspect = (1.0f * width) / height;
		float fNear = 0.01f;
		float fFar = 1000.0f;

		m_pCamera = new GLCamera(cameraEye, cameraLookAt, cameraUp, fovy, aspect, fNear, fFar);
		if (!m_pCamera)
		{
			throw "Exception";
			return;
		}

		const char* pczVertexShaderPath = "ShaderSource\\VertexShader.glsl";
		const char* pczFragmentShaderPath = "ShaderSource\\FragmentShader.glsl";

		auto strVertexShader = _getShaderSource(pczVertexShaderPath);
		auto strFragmentShader = _getShaderSource(pczFragmentShaderPath);

		const char* pczVertexShaderSource = strVertexShader.c_str();
		const char* pczFragmentShaderSource = strFragmentShader.c_str();

		m_pShaderProgram = new GLShaderProgram(&pczVertexShaderSource, &pczFragmentShaderSource, nullptr);
		if (!m_pShaderProgram)
		{
			return;
		}

		if (!m_pShaderProgram->Init())
		{
			return;
		}

		m_pMeshPass = new TriDObjectGLPass(m_pShaderProgram, m_pCamera);
		if (!m_pMeshPass)
		{
			return;
		}

		float cubeAABB[6] =
		{
			10.0f, 10.0f, 10.0f,
			20.0f, 20.0f, 20.0f,
		};

		auto _AABB = AABB(cubeAABB);
		LPtr<GLObject> pCube = _convertAABBtoGLObject(_AABB);
		//m_pMeshPass->AddGLObject(pCube);

		auto pDentalFile = CFileImportFactory::GetFileImportFactory()->LoadFile("fantasy_castle.stl");
 		LPtr<GLObject> pRenderObject = _convertModelFileToGLObject(pDentalFile);
		m_pMeshPass->AddGLObject(pRenderObject);
		
		auto& AABB = pDentalFile->GetAABB();
 		if (!AABB.GetAABBCenter(m_pCamera->m_fLookAt))
 		{
 			LeviathanOutStream << "[ERROR] Camera set lookAt failed." << std::endl;
 		}

		memcpy(m_pCamera->m_fEye, m_pCamera->m_fLookAt, sizeof(float) * 3);
		m_pCamera->m_fEye[0] -= (AABB.GetAABBRadius() * 2);

		auto AABBGLObject = _convertAABBtoGLObject(AABB);
		m_pMeshPass->AddGLObject(AABBGLObject);
		
		m_pMeshPass->SetPolygonMode(GL_LINE);
		m_pRenderWarpper->AddGLPass(TryCast<TriDObjectGLPass, GLPass>(m_pMeshPass));
	};

	void Scene::Update()
	{
		m_pRenderWarpper->Render();
	}

	std::string Scene::_getShaderSource(const char* pczShaderSourcePath)
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

	Leviathan::LPtr<Leviathan::GLObject> Scene::_convertModelFileToGLObject(LPtr<IModelFile> modelFile)
	{
		DynamicArray<float> glData(modelFile->GetTriangleCount() * 3 * 7 * sizeof(float));
		
		/*std::ofstream outFile("modelGLData.txt", std::ios::out);
		if (!outFile.is_open())
		{
			LeviathanOutStream << "[ERROR] Create file failed." << std::endl;
		}*/

		static float defaultColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
		bool bDefaultColor = false;
		
		auto color = modelFile->GetVertexColorArray();
		if (!color)
		{
			bDefaultColor = true;
		}

		for (unsigned i = 0; i < modelFile->GetTriangleCount(); i++)
		{
			unsigned* vertexIndex = modelFile->GetTriangleIndexArray() + 3 * i;

			for (unsigned j = 0; j < 3; j++)
			{
				float* vertexCoord = modelFile->GetVertex3DCoordArray() + 3 * vertexIndex[j];
				memcpy(glData.m_pData + 21 * i + 7 * j, vertexCoord, sizeof(float) * 3);
				
				if (bDefaultColor)
				{
					memcpy(glData.m_pData + 21 * i + 7 * j + 3, defaultColor, sizeof(float) * 4);
				}
				else
				{
					memcpy(glData.m_pData + 21 * i + 7 * j + 3, color + 4 * i, sizeof(float) * 4);
				}
			}
		}

		return new TriDGLObject(GL_TRIANGLES, glData.m_pData, modelFile->GetTriangleCount() * 3, TriDGLObject::VERTEX_ATTRIBUTE_XYZ | TriDGLObject::VERTEX_ATTRIBUTE_RGBA);
	}

	Leviathan::LPtr<Leviathan::GLObject> Scene::_convertAABBtoGLObject(const AABB& aabb)
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

		return new TriDGLObject(GL_TRIANGLES, cube, 36, TriDGLObject::VERTEX_ATTRIBUTE_XYZ | TriDGLObject::VERTEX_ATTRIBUTE_RGBA);
	}

	Leviathan::LPtr<Leviathan::GLObject> Scene::_getPointGLObject(float* pCoordData, unsigned uVertexCount, float *pColorData /*= nullptr*/)
	{
		static float defaultColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
		DynamicArray<float> pArray(uVertexCount * 7 * sizeof(float));
		for (unsigned i = 0; i < uVertexCount; i++)
		{
			memcpy(pArray.m_pData + 7 * i, pCoordData + 3 * i, sizeof(float) * 3);
			
			if (pColorData)
			{
				memcpy(pArray.m_pData + 7 * i + 3, pColorData + 4 * i, sizeof(float) * 4);
			}
			else
			{
				memcpy(pArray.m_pData + 7 * i + 3, defaultColor, sizeof(float) * 4);
			}
		}

		return new TriDGLObject(GL_POINTS, pArray.m_pData, uVertexCount, TriDGLObject::VERTEX_ATTRIBUTE_XYZ | TriDGLObject::VERTEX_ATTRIBUTE_RGBA);
	}
}