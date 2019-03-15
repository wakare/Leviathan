#include <fstream>
#include <string>
#include <sstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Camera.h"
#include "GLLight.h"
#include "CommonScene.h"
#include "DynamicArray.h"
#include "CFileImportFactory.h"
#include "GeometryCalculator.h"
#include "DrawableNode.h"
#include "SOIL.h"
#include "PictureObject.h"
#include "SceneNode.h"
#include "CMesh.h"
#include "RenderWrapper.h"
#include "TriDObjectGLPass.h"
#include "TriDGLObject.h"
#include "GLShaderProgram.h"
#include "IMesh.h"
#include "SceneGraph.h"
#include "SceneHelper.h"
#include "SceneLogicDataSet.h"
#include "SceneRenderDataSet.h"

namespace Leviathan
{
	CommonScene::CommonScene(GLFWwindow* pRenderWindow, int width, int height) :
		m_width(width), 
		m_height(height),
		IScene(),
		m_pGLFWWindow(pRenderWindow), 
		m_pRenderWarpper(nullptr), 
		m_pMeshPass(nullptr), 
		m_pShaderProgram(nullptr),
		m_pSceneLogicData(nullptr), 
		m_pSceneRenderData(nullptr)
	{
		m_pRenderWarpper = new RenderWrapper(pRenderWindow);

		if (!m_pRenderWarpper)
		{
			LeviathanOutStream << "[FATAL] RenderWrapper init failed." << std::endl;
			throw "exception";
			return;
		}

		if (!_initCamera(width, height))
		{
			LeviathanOutStream << "[FATAL] Scene camera init failed." << std::endl;
			throw "exception";
			return;
		}

		const char* pczVertexShaderPath = "ShaderSource\\VertexShader.glsl";
		const char* pczFragmentShaderPath = "ShaderSource\\FragmentShader.glsl";
		if (!SceneHelper::InitShaderSource(pczVertexShaderPath, pczFragmentShaderPath, m_pShaderProgram))
		{
			LeviathanOutStream << "[FATAL] Scene ShaderSource init failed." << std::endl;
			throw "exception";
			return;
		}

		m_pMeshPass = new TriDObjectGLPass(m_pShaderProgram, m_pCamera);
		if (!m_pMeshPass) return; 

		m_pRenderWarpper->AddGLPass(TryCast<TriDObjectGLPass, GLPass>(m_pMeshPass));
		m_pSceneLogicData = new SceneLogicDataSet(TryCast<TriDObjectGLPass, GLPass>(m_pMeshPass));
		m_pSceneRenderData = new SceneRenderDataSet();
	};

	CommonScene::~CommonScene()
	{

	}

	Leviathan::Camera& CommonScene::GetCamera()
	{
		return *m_pCamera;
	}

	const std::vector<Leviathan::LPtr<Leviathan::GLLight>>& CommonScene::GetLightVec() const
	{
		return m_pLights;
	}

	bool CommonScene::_firstUpdate()
	{
		return true;
	}

	void CommonScene::_generateWorldRayFromScreenCoord(unsigned x, unsigned y, float* rayPos, float* rayDir)
	{
		float _x = (1.0f * x) / (m_width);
		float _y = (1.0f * y) / (m_height);
		_x = 2 * (_x - 0.5f);
		_y = 2 * (_y - 0.5f);

		// NDC coord
		float temp[4] = { _x, _y, -1.0f, 1.0f };
		Eigen::Vector4f coord(temp);
		auto cameraCoord = m_pCamera->GetPerspectiveTransformMatrix().inverse() * coord ;
		auto worldCoord = m_pCamera->GetViewportTransformMatrix().inverse() * cameraCoord;

		rayPos[0] = m_pCamera->m_fEye[0];
		rayPos[1] = m_pCamera->m_fEye[1];
		rayPos[2] = m_pCamera->m_fEye[2];

		rayDir[0] = worldCoord[0] - rayPos[0];
		rayDir[1] = worldCoord[1] - rayPos[1];
		rayDir[2] = worldCoord[2] - rayPos[2];		
	}

	void CommonScene::_executeDataRequest()
	{
		m_dataRequestLock.lock();
		{
			for (auto& request : m_dataRequests)
			{
				request();
			}

			m_dataRequests.clear();
		}
		m_dataRequestLock.unlock();
	}

	bool CommonScene::_initCamera(unsigned uWidth, unsigned uHeight)
	{
		float cameraEye[3] = { 0.0f, 0.0f, -10.0f };
		float cameraLookAt[3] = { 0.0f, 0.0f, 0.0f };
		float cameraUp[3] = { 0.0f, 1.0f, 0.0f };

		float fovy = PI_FLOAT * (45.0f / 180.0f);
		float fAspect = (1.0f * uWidth) / uHeight;
		float fNear = 0.01f;
		float fFar = 100000.0f;

		m_pCamera = new Camera(cameraEye, cameraLookAt, cameraUp, fovy, fAspect, fNear, fFar);
		if (!m_pCamera)
		{
			throw "Exception";
			return false;
		}

		return true;
	}

	bool CommonScene::_initLight()
	{
		LPtr<GLLight> light = new GLLight({ 0.0f, 0.0f, -10.0f }, { 0.5f, 0.5f, 0.5f },
			{ 0.8f, 0.8f, 0.8f }, { 1.0f, 1.0f, 1.0f });

		m_pMeshPass->AddGLLight(light);
		m_pLights.push_back(light);
		return true;
	}

	void CommonScene::_resetCamera(float* coord/* = nullptr*/, float fDistance /* = -1.0f*/)
	{
		if (!coord)
		{
			auto AABB = m_pSceneLogicData->GetAABB();
			m_pCamera->LookAt(Eigen::Vector3f(AABB.center), fDistance);
		}
		else
		{
			m_pCamera->LookAt(Eigen::Vector3f(coord), fDistance);
		}
	}

	Leviathan::SceneLogicDataSet& CommonScene::GetSceneData()
	{
		return *m_pSceneLogicData;
	}

	void CommonScene::AddRequest(SceneDataRequestFunc func)
	{
		m_dataRequests.push_back(func);
	}

	void CommonScene::Update()
	{
		static bool bFirstUpdate = true;
		if (bFirstUpdate)
		{
			_firstUpdate();
			bFirstUpdate = false;
		}

		_executeDataRequest();

		m_pSceneLogicData->Update();
		m_pSceneRenderData->Update();
		m_pRenderWarpper->Render();
	}

	bool CommonScene::Pick(unsigned x, unsigned y)
	{
		float rayPos[3], rayDir[3];
		_generateWorldRayFromScreenCoord(x, y, rayPos, rayDir);
		PickInfo pickInfo;
		if (m_pSceneLogicData->Pick(rayPos, rayDir, pickInfo))
		{
			LogLine("Picked!");
			return true;
		}

		return false;
	}

	void CommonScene::SetViewport(int width, int height)
	{
		m_width = width;
		m_height = height;
	}

}