#pragma once
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "GLPass.h"

class RenderWrapper
{
public:
	RenderWrapper(GLFWwindow* pWindow) :m_pWindow(pWindow) {}
	void Render();
	bool AddGLPass(std::shared_ptr<GLPass> GLPass);
	bool DelGLPass(std::shared_ptr<GLPass> GLPass);
private:
	GLFWwindow* m_pWindow;
	std::vector<std::shared_ptr<GLPass>> m_GLPasses;
};