#include "TriDGLObject.h"

bool TriDGLObject::Init(GLuint primType, float* data, GLuint vertexSize)
{
	// GetVertexSize
	GLuint uFloatCountPerVertex = 0;
	if (m_vertexAttributeMask & VERTEX_ATTRIBUTE_XYZ)
	{
		uFloatCountPerVertex += 3;
	}

	if (m_vertexAttributeMask & VERTEX_ATTRIBUTE_RGBA)
	{
		uFloatCountPerVertex += 1;
	}

	if (m_vertexAttributeMask & VERTEX_ATTRIBUTE_NXYZ)
	{
		uFloatCountPerVertex += 3;
	}

	if (uFloatCountPerVertex == 0)
	{
		throw "TriDGLObject::Init() --> Invalid VertexAttribute Mask";
		return false;
	}

	// Init VAO
	glGenVertexArrays(1, &m_VAO);

	glBindVertexArray(m_VAO);
	/*glUseProgram(m_pShaderMgr->GetShaderProgram());*/

	// Create a buffer to store vertex.
	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	// Bind the triangle vertex data to buffer.
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * uFloatCountPerVertex * vertexSize, data, GL_STATIC_DRAW);

	GLuint positionIndex = 0u;
	GLuint uOffset = 0u;

	// Set position vector format
	if (m_vertexAttributeMask & VERTEX_ATTRIBUTE_XYZ)
	{
		glVertexAttribPointer(positionIndex, 3, GL_FLOAT, GL_FALSE, uFloatCountPerVertex * sizeof(GLfloat), (GLvoid*)uOffset);
		glEnableVertexAttribArray(positionIndex);

		positionIndex++;
		uOffset += 3 * sizeof(GLfloat);
	}

	// Set color vector format
	if (m_vertexAttributeMask & VERTEX_ATTRIBUTE_RGBA)
	{
		glVertexAttribPointer(positionIndex, 1, GL_FLOAT, GL_FALSE, uFloatCountPerVertex * sizeof(GLfloat), (GLvoid*)uOffset);
		glEnableVertexAttribArray(positionIndex);

		positionIndex++;
		uOffset += sizeof(GLfloat);
	}

	// Set normal vector format
	if (m_vertexAttributeMask & VERTEX_ATTRIBUTE_NXYZ)
	{
		glVertexAttribPointer(positionIndex, 3, GL_FLOAT, GL_FALSE, uFloatCountPerVertex * sizeof(GLfloat), (GLvoid*)(uOffset));
		glEnableVertexAttribArray(positionIndex);

		positionIndex++;
		uOffset += 3 * sizeof(GLfloat);
	}

	// Unbind VAO
	glBindVertexArray(0);

	return true;
}
