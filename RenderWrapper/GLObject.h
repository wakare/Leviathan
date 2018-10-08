#pragma once
#define GLEW_STATIC
#include <GL\glew.h>

class GLObject
{
public:
	GLObject(GLuint primType) :m_VAO(0), m_VBO(0), m_primitiveType(primType) {}
	GLuint GetVAO() { return m_VAO; }
	GLuint GetVBO() { return m_VBO; }
	GLuint GetPrimType() { return m_primitiveType; }
	GLuint GetVertexCount() { return m_vertexCount; }

	virtual bool Init() = 0;

protected:
	GLuint m_VAO;
	GLuint m_VBO;
	GLuint m_primitiveType;
	GLuint m_vertexCount;
};