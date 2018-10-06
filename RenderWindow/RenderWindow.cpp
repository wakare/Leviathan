#include "RenderWindow.h"

RenderWindow::RenderWindow(GLint width /*= 800*/, GLint height /*= 600*/, GLchar* pTitle /*= "RenderWindow"*/):
	m_width(width), m_height(height), m_pWindowTitle(pTitle)
{
	if (GLFW_FALSE == glfwInit())
	{
		throw "glfwInit() failed.";
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

bool RenderWindow::CreateWindow()
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

	m_pRenderWrapper = std::make_shared<RenderWrapper>(m_pWindow);
	if (!m_pRenderWrapper)
	{
		throw "RenderWrapper init failed.";
		return false;
	}

	return true;
}

void RenderWindow::Run()
{
	if (!m_pWindow)
	{
		if (!CreateWindow())
		{
			throw "CreateWindow failed.";
			return;
		}
	}

	while (!glfwWindowShouldClose(m_pWindow))
	{
		glfwPollEvents();
		m_pRenderWrapper->Render();
	}

	glfwTerminate();
	return;
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
