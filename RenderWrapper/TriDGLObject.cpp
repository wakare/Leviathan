#include "TriDGLObject.h"
#include "GlobalDef.h"

namespace Leviathan
{
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
			uFloatCountPerVertex += 4;
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

		GLuint uOffset = 0u;

		// Set position vector format
		if (m_vertexAttributeMask & VERTEX_ATTRIBUTE_XYZ)
		{
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, uFloatCountPerVertex * sizeof(GLfloat), (GLvoid*)uOffset);
			glEnableVertexAttribArray(0);

			uOffset += 3 * sizeof(GLfloat);
		}

		// Set color vector format
		if (m_vertexAttributeMask & VERTEX_ATTRIBUTE_RGBA)
		{
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, uFloatCountPerVertex * sizeof(GLfloat), (GLvoid*)uOffset);
			glEnableVertexAttribArray(1);

			uOffset += 4 * sizeof(GLfloat);
		}

		// Set normal vector format
		if (m_vertexAttributeMask & VERTEX_ATTRIBUTE_NXYZ)
		{
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, uFloatCountPerVertex * sizeof(GLfloat), (GLvoid*)(uOffset));
			glEnableVertexAttribArray(2);

			uOffset += 3 * sizeof(GLfloat);
		}

		// Unbind VBO
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// Unbind VAO
		glBindVertexArray(0);

		return true;
	}

	bool TriDGLObject::Render(GLuint shaderProgram)
	{
		// Set VertexTypeMask uniform
		GLint location = glGetUniformLocation(shaderProgram, "VertexTypeMask");
		if (location == -1)
		{
			LeviathanOutStream << "[ERROR] Get Uniform location failed." << std::endl;
			return false;
		}

		glUniform1ui(location, GetVertexMask());

		auto VAO = GetVAO();
		if (VAO == 0)
		{
			return false;
		}

		glBindVertexArray(VAO);
		glDrawArrays(GetPrimType(), 0, GetVertexCount());
		glBindVertexArray(0);

		return true;
	}

	bool TriDGLObject::SetMaterial(GLuint shaderProgram)
	{
		if (!m_pCommonGLMaterial)
		{
			return false;
		}

		return m_pCommonGLMaterial->SetMaterial(shaderProgram);
	}

	bool TriDGLObject::ApplyModelMatrix(Leviathan::LPtr<Leviathan::GLUniform>& modelMatrixUniform)
	{
		if (!modelMatrixUniform)
		{
			LeviathanOutStream << "[ERROR] modelUniform is nullptr." << std::endl;
			return false;
		}

		// Set modelMatrix
		if (!m_pModelMatrix)
		{
			float identityMatrix[16] = 
			{
				1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f,
			};

			m_pModelMatrix = new Matrix4f(identityMatrix);
		}

		modelMatrixUniform->SetData(m_pModelMatrix->GetData(), m_pModelMatrix->GetDataSize());

		return true;
	}

}