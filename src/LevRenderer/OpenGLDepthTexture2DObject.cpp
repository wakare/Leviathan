#include "OpenGLDepthTexture2DObject.h"

namespace Leviathan
{
	namespace Renderer
	{
		OpenGLDepthTexture2DObject::~OpenGLDepthTexture2DObject()
		{
			glDeleteTextures(1, &m_texture_object);
		}

		OpenGLDepthTexture2DObject::OpenGLDepthTexture2DObject(OpenGLObjectManager& manager,
			GLuint texture_object_uid, GLuint width, GLuint height, const GLvoid* data) : IOpenGLTextureObject(manager, texture_object_uid)
			, m_width(width)
			, m_height(height)
		{
			glGenTextures(1, &m_texture_object);
			glBindTexture(GL_TEXTURE_2D, m_texture_object);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, m_width, m_height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}
}
