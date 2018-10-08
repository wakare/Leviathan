#pragma once

#include "Scene.h"
#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <memory>

class Scene;

class RenderWindow
{
public:
	RenderWindow(GLint width = 800, GLint height = 600, GLchar* pTitle = "RenderWindow");
	bool CreateWindow();
	void Run();

	GLFWwindow* GetGLFWWindow() { return m_pWindow; };
	GLint GetWidth() { return m_width; };
	GLint GetHeight() { return m_height; };

private:
	bool _glewInit();

	GLint m_width;
	GLint m_height;
	GLchar* m_pWindowTitle;
	
	GLFWwindow* m_pWindow;
	std::shared_ptr<Scene> m_pScene;
};