#pragma once
#include "GLObject.h"

class TriDGLObject : public GLObject
{
public:
	enum VertexAttributeType
	{
		VERTEX_ATTRIBUTE_XYZ = 0x1,		// Coord XYZ
		VERTEX_ATTRIBUTE_RGBA = 0x2,	// Color RGBAs
		VERTEX_ATTRIBUTE_NXYZ = 0x4,	// Normal XYZ
	};

	TriDGLObject(GLuint primType, GLfloat* data, GLuint vertexSize, GLint vertexMask) :
		GLObject(primType, vertexSize), m_vertexAttributeMask(vertexMask), m_data(data)
	{
		Init();
	};

	virtual bool Init();

private:
	GLint m_vertexAttributeMask;
	GLfloat* m_data;
};