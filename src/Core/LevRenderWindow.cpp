#include "LevRenderWindow.h"
#include "Event.h"
#include "EventSystem.h"
#include "WindowCallBack.h"

namespace Leviathan
{
	LevRenderWindow::LevRenderWindow(LPtr<EventSystem> pEventSystem, int width /*= 1080*/, int height /*= 720*/, char* pTitle /*= (char*)"Leviathan"*/):
		m_width(width),
		m_height(height),
		m_pWindowTitle(pTitle),
		m_pWindow(nullptr),
		m_bRunning(false),
		m_pEventSystem(pEventSystem)
	{
		if (GLFW_FALSE == glfwInit())
		{
			throw "glfwInit() failed.";
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	}

	LevRenderWindow::~LevRenderWindow()
	{

	}

	bool LevRenderWindow::Create(int width, int height, int hParent /*= NULL*/)
	{
		m_width = width; m_height = height;
		m_pWindow = glfwCreateWindowEx(m_width, m_height, m_pWindowTitle, NULL, NULL, hParent);

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

		_setWindowProcess();

		return true;
	}

	void LevRenderWindow::Run()
	{
		if (!m_pWindow)
		{
			return;
		}

		m_bRunning = true;

		while (m_bRunning)
		{
			Update();
		}
	}

	void LevRenderWindow::Update()
	{
		if (glfwWindowShouldClose(m_pWindow))
		{
			m_bRunning = false;
			glfwTerminate();
			return;
		}

		glfwPollEvents();
	}

	void LevRenderWindow::Stop()
	{
		glfwSetWindowShouldClose(m_pWindow, true);
	}

	void LevRenderWindow::Accept(Event& event)
	{
		_handleInput(event);
	}

	void LevRenderWindow::_setWindowProcess()
	{
		if (m_pEventSystem)
		{
			WindowCallBack::m_spEventSystem = m_pEventSystem;
		}

		glfwSetKeyCallback(m_pWindow, (WindowCallBack::KeyCallback));
		glfwSetCursorPosCallback(m_pWindow, (WindowCallBack::MousePositionCallback));
		glfwSetScrollCallback(m_pWindow, (WindowCallBack::MouseScrollCallback));
		glfwSetMouseButtonCallback(m_pWindow, (WindowCallBack::MouseButtonCallBack));
		glfwSetWindowSizeCallback(m_pWindow, (WindowCallBack::ResizeCallback));
	}

	bool LevRenderWindow::_glewInit()
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

	void LevRenderWindow::_handleInput(Event& event)
	{
		if (_handleResize(event)) return;
	}

	bool LevRenderWindow::_handleResize(Event& event)
	{
		if (event.m_action != Event::RESIZE)
		{
			return false;
		}

		m_width = event.m_context.m_windowResizeSize.width;
		m_height = event.m_context.m_windowResizeSize.height;

		//m_pScene->SetViewport(m_width, m_height);
		glViewport(0, 0, m_width, m_height);

		return true;
	}

	int LevRenderWindow::GetWidth()
	{
		return m_width;
	}

	int LevRenderWindow::GetHeight()
	{
		return m_height;
	}

	int LevRenderWindow::GetWindowHandle() const
	{
		return (m_pWindow) ? (int)glfwGetWin32Window(m_pWindow) : NULL;
	}

	GLFWwindow* LevRenderWindow::GetGLFWWindow()
	{
		return m_pWindow;
	}

}