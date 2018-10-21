#pragma once

#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <memory>
#include "WindowCallBack.h"
#include "Scene.h"

class Scene;

class RenderWindow : public EventListener
{
public:
	RenderWindow(std::shared_ptr<EventSystem> pEventSystem, GLint width = 800, GLint height = 600, GLchar* pTitle = "RenderWindow");
	bool CreateRenderWindow();
	void Run();

	void Accept(Event event);

	GLFWwindow* GetGLFWWindow() { return m_pWindow; };
	GLint GetWidth() { return m_width; };
	GLint GetHeight() { return m_height; };

private:
	void _setWindowProcess();
	bool _glewInit();

	GLint m_width;
	GLint m_height;
	GLchar* m_pWindowTitle;

	GLFWwindow* m_pWindow;
	std::shared_ptr<Scene> m_pScene;
	std::shared_ptr<EventSystem> m_pEventSystem;
};