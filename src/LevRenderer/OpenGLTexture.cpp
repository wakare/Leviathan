#include "OpenGLTexture.h"

namespace Leviathan
{
	namespace Renderer
	{
		OpenGLTexture::OpenGLTexture(const Scene::LevTextureObject& texture) 
			: m_texture_uniform_name(texture.GetTextureUniformName())
			, m_texture_uniform_location(-1)
			, m_uWidth(texture.GetWidth())
			, m_uHeight(texture.GetHeight())
		{
			glGenTextures(1, &m_textureHandle);
			glBindTexture(GL_TEXTURE_2D, m_textureHandle);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_uWidth, m_uHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, texture.GetTextureData());
			glGenerateMipmap(GL_TEXTURE_2D);

			glBindTexture(GL_TEXTURE_2D, 0);
		}

		OpenGLTexture::~OpenGLTexture()
		{
			glDeleteTextures(1, &m_textureHandle);
		};

		GLboolean OpenGLTexture::ApplyTexture(GLuint shaderProgram, const char* samplerUniformName, GLuint textureUnitOffset /* = 0*/)
		{
			glActiveTexture(GL_TEXTURE0 + textureUnitOffset);
			glBindTexture(GL_TEXTURE_2D, m_textureHandle);

			if (m_texture_uniform_location == -1)
			{
				m_texture_uniform_location = glGetUniformLocation(shaderProgram, samplerUniformName);
				LEV_ASSERT(m_texture_uniform_location != -1);
			}

			glUniform1i(m_texture_uniform_location, textureUnitOffset);
			return GL_TRUE;
		}

		GLboolean OpenGLTexture::UnApplyTexture(GLuint shaderProgram, GLuint textureUnitOffset /* = 0*/)
		{
			glActiveTexture(GL_TEXTURE0 + textureUnitOffset);
			glBindTexture(GL_TEXTURE_2D, 0);

			return GL_TRUE;
		}

	}
}