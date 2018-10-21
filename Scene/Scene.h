#pragma once
#include "GLCamera.h"
#include "RenderWrapper.h"
#include "TriDObjectGLPass.h"
#include "TriDGLObject.h"
#include "GLShaderProgram.h"

class Scene
{
public:
	Scene(GLFWwindow* pRenderWindow, int width, int height);

	virtual void Update();

private:
	std::string _getShaderSource(const char* pczShaderSourcePath);

	GLFWwindow* m_pGLFWWindow;

	std::shared_ptr<GLCamera> m_pCamera;
	std::shared_ptr<RenderWrapper> m_pRenderWarpper;

	std::shared_ptr<TriDObjectGLPass> m_pMeshPass;
	std::shared_ptr<GLShaderProgram> m_pShaderProgram;
};