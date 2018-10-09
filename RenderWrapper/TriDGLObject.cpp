#include "TriDGLObject.h"

bool TriDGLObject::Init()
{
	// GetVertexSize
	GLuint uFloatCountPerVertex = 0;
	if (m_vertexAttributeMask & VERTEX_ATTRIBUTE_XYZ)
	{
		uFloatCountPerVertex += 3;
	}

	if (m_vertexAttributeMask & VERTEX_ATTRIBUTE_RGBA)
	{
		uFloatCountPerVertex += 3;
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

	// Create a buffer to store vertex.
	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	// Bind the triangle vertex data to buffer.
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * uFloatCountPerVertex * m_vertexCount, m_data, GL_STATIC_DRAW);

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
		glVertexAttribPointer(positionIndex, 3, GL_FLOAT, GL_FALSE, uFloatCountPerVertex * sizeof(GLfloat), (GLvoid*)uOffset);
		glEnableVertexAttribArray(positionIndex);

		positionIndex++;
		uOffset += 3 * sizeof(GLfloat);
	}

	// Set normal vector format
	if (m_vertexAttributeMask & VERTEX_ATTRIBUTE_NXYZ)
	{
		glVertexAttribPointer(positionIndex, 3, GL_FLOAT, GL_FALSE, uFloatCountPerVertex * sizeof(GLfloat), (GLvoid*)(uOffset));
		glEnableVertexAttribArray(positionIndex);

		positionIndex++;
		uOffset += 3 * sizeof(GLfloat);
	}

	// Unbind VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Unbind VAO
	glBindVertexArray(0);

	//GLfloat vertices[] = {
	//	0.5f,  0.5f, 0.0f,  // Top Right
	//	0.5f, -0.5f, 0.0f,  // Bottom Right
	//	-0.5f, -0.5f, 0.0f,  // Bottom Left
	//	-0.5f,  0.5f, 0.0f   // Top Left 
	//};
	//GLuint indices[] = {  // Note that we start from 0!
	//	0, 1, 3,  // First Triangle
	//	1, 2, 3   // Second Triangle
	//};
	//GLuint VBO, EBO;
	//glGenVertexArrays(1, &m_VAO);
	//glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);
	//// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	//glBindVertexArray(m_VAO);

	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	//glEnableVertexAttribArray(0);

	//glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

	//glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs), remember: do NOT unbind the EBO, keep it bound to this VAO
	//m_primitiveType = GL_TRIANGLES;
	//m_vertexCount = 6;

	return true;
}
