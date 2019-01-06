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
		if (!m_pMeshPass)
		{
			return;
		}

		m_pSceneGraph = new SceneGraph(TryCast<TriDObjectGLPass, GLPass>(m_pMeshPass));
		m_pRenderWarpper->AddGLPass(TryCast<TriDObjectGLPass, GLPass>(m_pMeshPass));
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

	bool CommonScene::_dataUpdate()
	{
		m_dataUpdateRequestQueueLock.lock();

		for (auto& request : m_dataUpdateResquestQueue)
		{
			request();
		}

		m_dataUpdateResquestQueue.clear();
		m_dataUpdateRequestQueueLock.unlock();
		return true;
	}

	bool CommonScene::_firstUpdate()
	{
		return true;
	}

	bool CommonScene::_initSceneObject()
	{
		return true;
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
		LPtr<GLLight> light = new GLLight({ -100.0f, 100.0f, 10.0f }, { 0.5f, 0.5f, 0.5f },
			{ 0.8f, 0.8f, 0.8f }, { 1.0f, 1.0f, 1.0f });

		m_pMeshPass->AddGLLight(light);
		m_pLights.push_back(light);
		return true;
	}

	void CommonScene::_resetCamera(float* coord/* = nullptr*/, float fDistance /* = -1.0f*/)
	{
		if (!coord)
		{
			auto AABB = m_pSceneGraph->GetAABB();
			float center[3];
			AABB.GetAABBCenter(center);

			m_pCamera->LookAt(Vector4f(center), fDistance);
		}
		else
		{
			m_pCamera->LookAt(Vector4f(coord), fDistance);
		}
	}

	bool CommonScene::PushDataUpdateRequest(DataUpdateRequest request)
	{
		m_dataUpdateRequestQueueLock.lock();
		m_dataUpdateResquestQueue.push_back(request);
		m_dataUpdateRequestQueueLock.unlock();

		return true;
	}

	bool CommonScene::PushDataUpdateRequest(const std::vector<DataUpdateRequest>& request)
	{
		m_dataUpdateRequestQueueLock.lock();
		m_dataUpdateResquestQueue.insert(m_dataUpdateResquestQueue.end(), request.begin(), request.end());
		m_dataUpdateRequestQueueLock.unlock();

		return true;
	}

	bool CommonScene::AddNode(LPtr<Node<SceneNode>> pNode)
	{
		EXIT_GET_FALSE(m_pSceneGraph->AddNode(pNode));

		return true;
	}

	void CommonScene::Update()
	{
		static bool bFirstUpdate = true;
		if (bFirstUpdate)
		{
			_firstUpdate();
			bFirstUpdate = false;
		}

		_dataUpdate();
		m_pSceneGraph->Update();
		m_pRenderWarpper->Render();
	}
}