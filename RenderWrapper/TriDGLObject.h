#pragma once
#include "GLObject.h"

class TriDGLObject : public GLObject
{
public:
	

	TriDGLObject(GLuint primType, GLfloat* data, GLuint vertexSize, GLint vertexMask) :
		GLObject(primType, vertexSize, vertexMask), m_data(data)
	{
		Init();
	};

	virtual bool Init();
	virtual bool Render(GLuint shaderProgram);

private:
	
	GLfloat* m_data;
};