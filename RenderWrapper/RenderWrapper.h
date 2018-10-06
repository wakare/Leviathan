#pragma once

#include <GLFW/glfw3.h>
class RenderWrapper
{
public:
	RenderWrapper(GLFWwindow* pWindow) :m_pWindow(pWindow) {}
	void Render();

private:
	GLFWwindow* m_pWindow;
};