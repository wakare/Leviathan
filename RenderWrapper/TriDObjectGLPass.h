#pragma once
#include "GLPass.h"
#include "GLCamera.h"

class TriDObjectGLPass : public GLPass
{
public:
	TriDObjectGLPass(std::shared_ptr<GLShaderProgram> shaderProgram, std::shared_ptr<GLCamera> camera) :
		GLPass(shaderProgram), 
		m_bInited(false),
		m_mainCamera(camera)
	{
	};

	virtual bool Init();
	virtual void Render();

private:
	void _updateCameraMatrixUniform(GLuint shaderProgram);

	bool m_bInited;
	std::shared_ptr<GLCamera> m_mainCamera;
};