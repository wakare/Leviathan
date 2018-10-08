#pragma once
#include "GLPass.h"

class TriDObjectGLPass : public GLPass
{
public:
	TriDObjectGLPass(std::shared_ptr<GLShaderProgram> shaderProgram) :
		GLPass(shaderProgram)
	{
	};

	virtual bool Init();
	virtual void Render();
};