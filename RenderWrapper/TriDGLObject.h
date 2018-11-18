#pragma once
#include "GLObject.h"
namespace Leviathan
{
	class TriDGLObject : public GLObject
	{
	public:
		TriDGLObject(GLuint primType, GLfloat* data, GLuint vertexSize, GLint vertexMask) :
			GLObject(primType, vertexSize, vertexMask), m_data(data)
		{
			Init();
		};

		bool Init();
		bool Render(GLuint shaderProgram);

	private:

		GLfloat* m_data;
	};
}