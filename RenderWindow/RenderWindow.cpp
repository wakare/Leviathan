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

void RenderWindow::Accept(Event event)
{
	if (event.m_action == Event::InputAction::KEYDOWN && event.m_code == Event::InputCode::KEY_Z)
	{
		std::cout << "Key Z down." << std::endl;
	}
}

void RenderWindow::_setWindowProcess()
{
	if (m_pEventSystem)
	{
		WindowCallBack::m_spEventSystem = m_pEventSystem;
	}

	glfwSetKeyCallback(m_pWindow, (WindowCallBack::KeyCallback));
	glfwSetCursorPosCallback(m_pWindow, (WindowCallBack::MousePositionCallback));
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
