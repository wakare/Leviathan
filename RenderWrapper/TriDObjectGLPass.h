#pragma once
#include "GLPass.h"

class TriDObjectGLPass : public GLPass
{
public:
	TriDObjectGLPass(std::shared_ptr<GLShaderProgram> shaderProgram) :
		GLPass(shaderProgram), m_bInited(false)
	{
	};

	virtual bool Init();
	virtual void Render();

private:
	bool m_bInited;
};