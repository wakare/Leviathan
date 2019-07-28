#include "OpenGLTextureObject.h"

namespace Leviathan
{
	namespace Renderer
	{
		OpenGLTextureObject::OpenGLTextureObject(GLuint width, GLuint height, const GLvoid* data)
			: m_width(width)
			, m_height(height)
			, m_texture_unit_offset(0)
			, m_texture_object(0)
		{
			glGenTextures(1, &m_texture_object);
			glBindTexture(GL_TEXTURE_2D, m_texture_object);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			glBindTexture(GL_TEXTURE_2D, 0);
		}

		OpenGLTextureObject::~OpenGLTextureObject()
		{
			glDeleteTextures(1, &m_texture_object);
		}

		GLuint OpenGLTextureObject::GetTextureObject() const
		{
			return m_texture_object;
		}

		void OpenGLTextureObject::SetTextureUnitOffset(GLuint unit_offset)
		{
			m_texture_unit_offset = unit_offset;
		}

		GLuint OpenGLTextureObject::GetTextureUnitOffset() const
		{
			return m_texture_unit_offset;
		}
	}
}