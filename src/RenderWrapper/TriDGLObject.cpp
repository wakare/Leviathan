#include "TriDGLObject.h"
#include "GlobalDef.h"

namespace Leviathan
{
	bool TriDGLObject::Init()
	{
		m_bUseIndexArray = (m_pIndexData != nullptr);

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

		if (m_vertexAttributeMask & VERTEX_ATTRIBUTE_TEX)
		{
			uFloatCountPerVertex += 2;
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
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * uFloatCountPerVertex * m_vertexCount, m_pData, GL_STATIC_DRAW);

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
		
		// Set texture coordination format
		if (m_vertexAttributeMask & VERTEX_ATTRIBUTE_TEX)
		{
			glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, uFloatCountPerVertex * sizeof(GLfloat), (GLvoid*)(uOffset));
			glEnableVertexAttribArray(3);

			uOffset += 2 * sizeof(GLfloat);
		}

		// Set index buffer
		if (m_bUseIndexArray)
		{
			glGenBuffers(1, &m_IBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * m_uIndexArrayCount, m_pIndexData, GL_STATIC_DRAW);
			
			// Unbind IBO
			//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

		// Unbind VBO
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// Unbind VAO
		glBindVertexArray(0);

		// Reset data pointer
		m_pData = nullptr;
		m_pIndexData = nullptr;

		return true;
	}

	bool TriDGLObject::Render(GLuint shaderProgram)
	{
		EXIT_GET_FALSE(_updateVertexMaskUniform(shaderProgram));
		EXIT_GET_FALSE(_updateDefaultUseVertexColorUniform(shaderProgram));

		auto VAO = GetVAO();
		EXIT_GET_FALSE(VAO);
		glBindVertexArray(VAO);

		m_bUseIndexArray ? (glDrawElements(GetPrimType(), m_uIndexArrayCount, GL_UNSIGNED_INT, 0)) : (glDrawArrays(GetPrimType(), 0, GetVertexCount()));

		glBindVertexArray(0);

		return true;
	}

	bool TriDGLObject::ApplyMaterial(GLuint shaderProgram)
	{
		if (m_pCommonGLMaterial)
		{
			return m_pCommonGLMaterial->ApplyMaterial(shaderProgram);
		}
		
		return false;
	}

	bool TriDGLObject::UnApplyMaterial(GLuint shaderProgram)
	{

		return true;
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
			float fIdentityMatrix[16] = 
			{
				1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f,
			};

			m_pModelMatrix = new Matrix4f(fIdentityMatrix);
		}

		modelMatrixUniform->SetData(m_pModelMatrix->GetData(), m_pModelMatrix->GetDataSize());

		return true;
	}

	bool TriDGLObject::_updateDefaultUseVertexColorUniform(GLuint shaderProgram)
	{
		GLint nUseDefaultVertexColorEnableUniformLocation = glGetUniformLocation(shaderProgram, "UseDefaultVertexColor");
		if (nUseDefaultVertexColorEnableUniformLocation == -1)
		{
			LeviathanOutStream << "[ERROR] Get UseDefaultVertexColor uniform failed." << std::endl;
			return false;
		}

		glUniform1i(nUseDefaultVertexColorEnableUniformLocation, m_bUseDefaultVertexColor);
		return true;
	}

	bool TriDGLObject::_updateVertexMaskUniform(GLuint shaderProgram)
	{
		// Set VertexTypeMask uniform
		GLint uVertexTypeMaskLocation = glGetUniformLocation(shaderProgram, "VertexTypeMask");
		if (uVertexTypeMaskLocation == -1)
		{
			LeviathanOutStream << "[ERROR] Get uVertexTypeMaskLocation failed." << std::endl;
			return false;
		}

		glUniform1ui(uVertexTypeMaskLocation, GetVertexMask());
	}

}