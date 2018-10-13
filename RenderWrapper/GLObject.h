#pragma once
#define GLEW_STATIC
#include <GL\glew.h>

class GLObject
{
public:
	enum VertexAttributeType
	{
		VERTEX_ATTRIBUTE_XYZ = 0x1,		// Coord XYZ
		VERTEX_ATTRIBUTE_RGBA = 0x2,	// Color RGBAs
		VERTEX_ATTRIBUTE_NXYZ = 0x4,	// Normal XYZ
	};

	GLObject(GLuint primType, GLuint vertexCount, GLint vertexMask) :m_VAO(0), m_VBO(0), m_primitiveType(primType),m_vertexCount(vertexCount),m_vertexAttributeMask(vertexMask) {}
	GLuint GetVAO() { return m_VAO; }
	GLuint GetVBO() { return m_VBO; }
	GLuint GetPrimType() { return m_primitiveType; }
	GLuint GetVertexCount() { return m_vertexCount; }
	GLuint GetVertexMask() { return m_vertexAttributeMask; }

	virtual bool Init() = 0;
	virtual bool Render(GLuint shaderProgram) = 0;

protected:
	GLuint m_VAO;
	GLuint m_VBO;
	GLuint m_primitiveType;
	GLuint m_vertexCount;
	GLint m_vertexAttributeMask;
};