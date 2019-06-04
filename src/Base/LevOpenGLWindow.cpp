#include "LevOpenGLWindow.h"
#include "Event.h"

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#include "WindowCallBack.h"

namespace Leviathan
{
	LevOpenGLWindow::LevOpenGLWindow(int width, int height, char * pTitle)
		: m_width(width)
		, m_height(height)
		, m_pWindowTitle(pTitle)
		, m_pWindow(nullptr)
		, m_bRunning(false)
		, m_bStopped(false)
	{
		if (GLFW_FALSE == glfwInit())
		{
			throw "glfwInit() failed.";
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		AddEventListener(EventType::INPUT_EVENT, this);
	}

	bool LevOpenGLWindow::Create(int width, int height, int hParent)
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

	void LevOpenGLWindow::Run()
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

	void LevOpenGLWindow::Update()
	{
		if (glfwWindowShouldClose(m_pWindow))
		{
			m_bRunning = false;
			glfwTerminate();
			return;
		}

		glfwPollEvents();
	}

	void LevOpenGLWindow::SetStop()
	{
		glfwSetWindowShouldClose(m_pWindow, true);

		m_bStopped = true;
	}

	bool LevOpenGLWindow::Stoped()
	{
		return m_bStopped;
	}

	void LevOpenGLWindow::Accept(Event & event)
	{
		_handleInput(event);
	}

	int LevOpenGLWindow::GetWidth() const
	{
		return m_width;
	}

	int LevOpenGLWindow::GetHeight() const
	{
		return m_height;
	}

	int LevOpenGLWindow::GetWindowHandle() const
	{
		return (m_pWindow) ? (int)glfwGetWin32Window(m_pWindow) : NULL;
	}

	void LevOpenGLWindow::SwapBuffer()
	{
		glfwSwapBuffers(m_pWindow);
	}

	void LevOpenGLWindow::_setWindowProcess()
	{
		WindowCallBack::m_spEventSystem = this;

		glfwSetKeyCallback(m_pWindow, WindowCallBack::KeyCallback);
		glfwSetCursorPosCallback(m_pWindow, WindowCallBack::MousePositionCallback);
		glfwSetScrollCallback(m_pWindow, WindowCallBack::MouseScrollCallback);
		glfwSetMouseButtonCallback(m_pWindow, WindowCallBack::MouseButtonCallBack);
		glfwSetWindowSizeCallback(m_pWindow, WindowCallBack::ResizeCallback);
	}

	bool LevOpenGLWindow::_glewInit()
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

	void LevOpenGLWindow::_handleInput(Event & event)
	{
		if (_handleResize(event)) return;
	}

	bool LevOpenGLWindow::_handleResize(Event & event)
	{
		if (event.m_action != Event::RESIZE)
		{
			return false;
		}

		m_width = event.m_context.m_windowResizeSize.width;
		m_height = event.m_context.m_windowResizeSize.height;

		glViewport(0, 0, m_width, m_height);

		return true;
	}

	

}