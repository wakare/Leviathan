#include "OpenGL3DObject.h"
#include "OpenGLUniform.h"
#include "OpenGLShaderProgram.h"
#include "OpenGLMaterial.h"

namespace Leviathan
{
	namespace Renderer
	{
		OpenGL3DObject::OpenGL3DObject(unsigned id, GLuint primType, GLfloat* pVertexArrayData, GLuint vertexSize, GLint vertexMask, LPtr<OpenGLMaterial> pMaterial /*= nullptr*/, unsigned* pIndexArrayData /*= nullptr*/, unsigned uIndexArrayCount /*= 0U*/) :
			OpenGLObject(id, primType, vertexSize, vertexMask, pMaterial),
			m_pData(pVertexArrayData),
			m_pIndexData(pIndexArrayData),
			m_uIndexArrayCount(uIndexArrayCount)
		{
			Init();
		}

		bool OpenGL3DObject::SetLightEnable(bool enable)
		{
			m_pLightEnableUniform->SetData(enable);
			return true;
		}

		bool OpenGL3DObject::SetVertexMask(unsigned mask)
		{
			m_pVertexMaskUniform->SetData(mask);
			return true;
		}

		bool OpenGL3DObject::SetUseDefaultColor(bool use)
		{
			m_pUseDefaultColorUniform->SetData(use);
			return true;
		};

		bool OpenGL3DObject::Init()
		{
			m_bUseIndexArray = (m_pIndexData != nullptr);

			// GetVertexSize
			GLuint uFloatCountPerVertex = 0;

			if (m_vertexAttributeMask & VERTEX_ATTRIBUTE_XYZ)  uFloatCountPerVertex += 3;
			if (m_vertexAttributeMask & VERTEX_ATTRIBUTE_RGBA)  uFloatCountPerVertex += 4;
			if (m_vertexAttributeMask & VERTEX_ATTRIBUTE_NXYZ) uFloatCountPerVertex += 3;
			if (m_vertexAttributeMask & VERTEX_ATTRIBUTE_TEX)  uFloatCountPerVertex += 2;

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

			// Set uniform

			// Set light enable
			m_pLightEnableUniform = new OpenGLUniform("bLightOpen", OpenGLUniform::TYPE_BOOLEAN);
			m_pUniforms.push_back(m_pLightEnableUniform);
			SetLightEnable(m_vertexAttributeMask & VERTEX_ATTRIBUTE_NXYZ);

			// Set vertex mask
			m_pVertexMaskUniform = new OpenGLUniform("VertexTypeMask", OpenGLUniform::TYPE_UNSIGNED_INTEGER);
			m_pUniforms.push_back(m_pVertexMaskUniform);
			SetVertexMask(m_vertexAttributeMask);

			// Set use default color
			m_pUseDefaultColorUniform = new OpenGLUniform("UseDefaultVertexColor", OpenGLUniform::TYPE_BOOLEAN);
			m_pUniforms.push_back(m_pUseDefaultColorUniform);
			SetUseDefaultColor(false);

			return true;
		}

		bool OpenGL3DObject::Update()
		{
			return true;
		}

		bool OpenGL3DObject::Render(GLuint shaderProgram)
		{
			EXIT_IF_FALSE(ApplyUniform(shaderProgram));

			auto VAO = GetVAO();
			EXIT_IF_FALSE(VAO);
			glBindVertexArray(VAO);

			m_bUseIndexArray ? (glDrawElements(GetPrimType(), m_uIndexArrayCount, GL_UNSIGNED_INT, 0)) : (glDrawArrays(GetPrimType(), 0, GetVertexCount()));
			glBindVertexArray(0);

			return true;
		}
	}
}