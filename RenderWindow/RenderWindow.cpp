#include "RenderWindow.h"
#include <iostream>

RenderWindow::RenderWindow(std::shared_ptr<EventSystem> pEventSystem, GLint width /*= 800*/, GLint height /*= 600*/, GLchar* pTitle /*= "RenderWindow"*/) :
	m_pEventSystem(pEventSystem), m_width(width), m_height(height), m_pWindowTitle(pTitle), m_pWindow(nullptr)
{
	if (GLFW_FALSE == glfwInit())
	{
		throw "glfwInit() failed.";
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
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

	m_pScene = std::make_shared<Scene>(m_pWindow, GetWidth(), GetHeight());
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

	glfwTerminate();
	return;
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

	if ((event.m_action == Event::InputAction::KEYDOWN || event.m_action == Event::InputAction::REPERT) && event.m_code == Event::InputCode::KEY_Q)
	{
		fTranslate[2] += 0.02f;
	}

	if ((event.m_action == Event::InputAction::KEYDOWN || event.m_action == Event::InputAction::REPERT) && event.m_code == Event::InputCode::KEY_E)
	{
		fTranslate[2] -= 0.02f;
	}

	if (fTranslate[0] != 0.0f || fTranslate[1] != 0.0f || fTranslate[2] != 0.0f)
	{
		m_pScene->m_pCamera->Translate(fTranslate[0], fTranslate[1], fTranslate[2]);
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
			delta[0] /= (2 * 3.1415926f);
			delta[1] /= (2 * 3.1415926f);
			
			m_pScene->m_pCamera->Rotate(delta[1], delta[0], 0.0f);

			std::cout << "Delta mouseCoord = " << delta[0] << " " << delta[1] << std::endl;
		}
	}

	lastMouseXY = event.m_mouseCoord;
#pragma endregion update camera rotation
}

void RenderWindow::Accept(Event event)
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
