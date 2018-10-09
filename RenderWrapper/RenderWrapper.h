#pragma once
#include "GLPass.h"
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class RenderWrapper
{
public:
	RenderWrapper(GLFWwindow* pWindow) :m_pWindow(pWindow),m_bPreInited(false) {}
	void PreInit();
	void Render();
	bool AddGLPass(std::shared_ptr<GLPass> GLPass);
	bool DelGLPass(std::shared_ptr<GLPass> GLPass);
private:

	GLboolean m_bPreInited;
	GLFWwindow* m_pWindow;
	std::vector<std::shared_ptr<GLPass>> m_GLPasses;
};