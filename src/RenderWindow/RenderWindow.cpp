#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "RenderWindow.h"
#include "WindowCallBack.h"
#include "CommonScene.h"
#include "PointCloudScene.h"
#include "CFileImportFactory.h"
#include "GlobalDef.h"
#include "ImporterRegister.h"
#include "Camera.h"
#include "GLLight.h"
#include "TriDScene.h"

namespace Leviathan
{
	RenderWindow::RenderWindow(LPtr<EventSystem> pEventSystem, IScene::ESceneType sceneType, int width /*= 800*/, int height /*= 600*/, char* pTitle /*= "RenderWindow"*/) :
		m_pEventSystem(pEventSystem), 
		m_pFileImporter(nullptr),
		m_pScene(nullptr), 
		m_width(width), 
		m_height(height), 
		m_pWindowTitle(pTitle),
		m_pWindow(nullptr),
		m_bRunning(false),
		m_sceneType(sceneType)
	{
		if (GLFW_FALSE == glfwInit())
		{
			throw "glfwInit() failed.";
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_pFileImporter = CFileImportFactory::GetFileImportFactory();
		RegisterImporter();
	}

	RenderWindow::~RenderWindow()
	{

	}

	bool RenderWindow::CreateRenderWindow()
	{
		m_pWindow = glfwCreateWindow(m_width, m_height, m_pWindowTitle, NULL, NULL);

		if (m_pWindow == NULL)
		{
			throw "Failed to create GLFW window";
			glfwTerminate();
			return false;
		}

		glfwMakeContextCurrent(m_pWindow);
		if (!_glewInit())
		{
			throw "glewInit failed.";
			return false;
		}

		switch (m_sceneType)
		{
		case Leviathan::IScene::EST_COMMON:
			m_pScene = new CommonScene(m_pWindow, GetWidth(), GetHeight());
			break;

		case Leviathan::IScene::EST_POINTCLOUD:
			m_pScene = new PointCloudScene(m_pWindow, GetWidth(), GetHeight());
			break;

		case Leviathan::IScene::EST_TRID:
			m_pScene = new TriDScene(m_pWindow, GetWidth(), GetHeight());
			break;

		default:
			break;
		};

		if (!m_pScene)
		{
			throw "RenderWrapper init failed.";
			return false;
		}

		_setWindowProcess();

		return true;
	}

	void RenderWindow::Run()
	{
		m_bRunning = true;

		if (!m_pWindow)
		{
			if (!CreateRenderWindow())
			{
				throw "CreateWindow failed.";
				return;
			}
		}

		while (!glfwWindowShouldClose(m_pWindow))
		{
			glfwPollEvents();
			m_pScene->Update();

			if (m_pEventSystem)
			{
				m_pEventSystem->DispatchEvent();
			}
		}

		m_bRunning = false;
		glfwTerminate();
		return;
	}

	void RenderWindow::SyncStop()
	{
		glfwSetWindowShouldClose(m_pWindow, true);
		while (m_bRunning)
		{
			Sleep(100);
		}
	}

	void RenderWindow::_updateCameraTransform(Event& event)
	{
#pragma region Update transform
		float fTranslate[3] = { 0.0f };
		if ((event.m_action == Event::InputAction::KEYDOWN || event.m_action == Event::InputAction::REPERT) && event.m_code == Event::InputCode::KEY_W)
		{
			fTranslate[1] += 0.02f;
		}

		if ((event.m_action == Event::InputAction::KEYDOWN || event.m_action == Event::InputAction::REPERT) && event.m_code == Event::InputCode::KEY_S)
		{
			fTranslate[1] -= 0.02f;
		}

		if ((event.m_action == Event::InputAction::KEYDOWN || event.m_action == Event::InputAction::REPERT) && event.m_code == Event::InputCode::KEY_A)
		{
			fTranslate[0] += 0.02f;
		}

		if ((event.m_action == Event::InputAction::KEYDOWN || event.m_action == Event::InputAction::REPERT) && event.m_code == Event::InputCode::KEY_D)
		{
			fTranslate[0] -= 0.02f;
		}

		if ((event.m_action == Event::InputAction::SCROLL))
		{
			fTranslate[2] += (event.m_mouseScrollState.y * 0.02f);
		}

		if (fTranslate[0] != 0.0f || fTranslate[1] != 0.0f || fTranslate[2] != 0.0f)
		{
			m_pScene->GetCamera().MouseTranslate(fTranslate[0], fTranslate[1], fTranslate[2]);
		}
#pragma endregion

#pragma region update camera rotation
		float fRotate[3] = { 0.0f, 0.0f, 0.0f };
		static MouseCoord lastMouseXY = MouseCoord(-1, -1);

		static bool bMouseDown = false;
		if (event.m_action == Event::InputAction::KEYDOWN && event.m_code == Event::InputCode::MOUSE_LBUTTON)
		{
			bMouseDown = true;
		}

		if (event.m_action == Event::InputAction::KEYUP && event.m_code == Event::InputCode::MOUSE_LBUTTON)
		{
			bMouseDown = false;
		}

		if (bMouseDown)
		{
			if (lastMouseXY.x >= 0 && lastMouseXY.y >= 0)
			{
				float delta[2] = { event.m_mouseCoord.x - lastMouseXY.x, event.m_mouseCoord.y - lastMouseXY.y };
				delta[0] = ANGLE_TO_RADIAN(delta[0] * 0.1f);
				delta[1] = ANGLE_TO_RADIAN(delta[1] * 0.1f);

				m_pScene->GetCamera().MouseRotate(delta[0], delta[1]);
			}
		}

		lastMouseXY = event.m_mouseCoord;
#pragma endregion

		// Update light position as camera move
		for (auto& pLight : m_pScene->GetLightVec())
		{
			pLight->SetLightCoord({ m_pScene->GetCamera().m_fEye[0], m_pScene->GetCamera().m_fEye[1], m_pScene->GetCamera().m_fEye[2] });
		}
	}

	void RenderWindow::Accept(Event& event)
	{
		_updateCameraTransform(event);
	}

	void RenderWindow::_setWindowProcess()
	{
		if (m_pEventSystem)
		{
			WindowCallBack::m_spEventSystem = m_pEventSystem;
		}

		glfwSetKeyCallback(m_pWindow, (WindowCallBack::KeyCallback));
		glfwSetCursorPosCallback(m_pWindow, (WindowCallBack::MousePositionCallback));
		glfwSetScrollCallback(m_pWindow, (WindowCallBack::MouseScrollCallback));
		glfwSetMouseButtonCallback(m_pWindow, (WindowCallBack::MouseButtonCallBack));
	}

	bool RenderWindow::_glewInit()
	{
		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK)
		{
			throw "Failed to initialize GLEW";
			return false;
		}

		int width, height;
		glfwGetFramebufferSize(m_pWindow, &width, &height);
		glViewport(0, 0, width, height);

		return true;
	}
}