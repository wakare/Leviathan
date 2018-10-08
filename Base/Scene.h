#pragma once
#include "RenderWindow.h"
#include "GLCamera.h"
#include "RenderWrapper.h"
#include "TriDObjectGLPass.h"
#include "TriDGLObject.h"
#include "GLShaderProgram.h"

class RenderWindow;

class Scene
{
public:
	Scene(RenderWindow& pRenderWindow);

	virtual void Update();

private:
	std::string _getShaderSource(const char* pczShaderSourcePath);

	RenderWindow& m_refRenderWindow;

	std::shared_ptr<GLCamera> m_pCamera;
	std::shared_ptr<RenderWrapper> m_pRenderWarpper;

	std::shared_ptr<TriDObjectGLPass> m_pMeshPass;
	std::shared_ptr<GLShaderProgram> m_pShaderProgram;
};