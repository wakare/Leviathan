#pragma once

#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <memory>
#include "RenderWrapper.h"

class RenderWindow
{
public:
	RenderWindow(GLint width = 800, GLint height = 600, GLchar* pTitle = "RenderWindow");
	bool CreateWindow();
	void Run();
private:
	bool _glewInit();

	GLint m_width;
	GLint m_height;
	GLchar* m_pWindowTitle;
	
	GLFWwindow* m_pWindow;
	std::shared_ptr<RenderWrapper> m_pRenderWrapper;
};