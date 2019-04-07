#include "OpenGLTexture.h"

namespace Leviathan
{
	namespace Renderer
	{
		OpenGLTexture::OpenGLTexture(unsigned char* pData, unsigned uWidth, unsigned uHeight) :
			m_uWidth(uWidth),
			m_uHeight(uHeight)
		{
			glGenTextures(1, &m_textureHandle);
			glBindTexture(GL_TEXTURE_2D, m_textureHandle);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, uWidth, uHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, pData);
			glGenerateMipmap(GL_TEXTURE_2D);

			glBindTexture(GL_TEXTURE_2D, 0);
		};

		GLboolean OpenGLTexture::ApplyTexture(GLuint textureUnitOffset, GLuint shaderProgram, const char* samplerUniformName)
		{
			glActiveTexture(GL_TEXTURE0 + textureUnitOffset);
			glBindTexture(GL_TEXTURE_2D, m_textureHandle);

			GLint samplerUniformLocation = glGetUniformLocation(shaderProgram, samplerUniformName);
			if (samplerUniformLocation == -1)
			{
				return GL_FALSE;
			}

			glUniform1i(samplerUniformLocation, textureUnitOffset);

			return GL_TRUE;
		}

		GLboolean OpenGLTexture::UnApplyTexture(GLuint textureUnitOffset, GLuint shaderProgram)
		{
			glActiveTexture(GL_TEXTURE0 + textureUnitOffset);
			glBindTexture(GL_TEXTURE_2D, 0);

			return true;
		}

	}
}