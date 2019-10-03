#include "OpenGLDepthTexture2DObject.h"
#include "OpenGLObjectManager.h"

namespace Leviathan
{
	namespace Renderer
	{
		OpenGLDepthTexture2DObject::~OpenGLDepthTexture2DObject()
		{
			IOO_PUSH_SYNC_RENDER_COMMAND(glDeleteTextures(1, &m_texture_object));
		}

		OpenGLDepthTexture2DObject::OpenGLDepthTexture2DObject(OpenGLObjectManager& manager,
			GLuint texture_object_uid, GLuint width, GLuint height, const GLvoid* data) : IOpenGLTextureObject(manager, texture_object_uid)
			, m_width(width)
			, m_height(height)
		{
			IOO_PUSH_SYNC_RENDER_COMMAND(glGenTextures(1, &m_texture_object));
			IOO_PUSH_SYNC_RENDER_COMMAND(glBindTexture(GL_TEXTURE_2D, m_texture_object));

			IOO_PUSH_SYNC_RENDER_COMMAND(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
			IOO_PUSH_SYNC_RENDER_COMMAND(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

			IOO_PUSH_SYNC_RENDER_COMMAND(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
			IOO_PUSH_SYNC_RENDER_COMMAND(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

			IOO_PUSH_SYNC_RENDER_COMMAND(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, m_width, m_height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, data));
			IOO_PUSH_SYNC_RENDER_COMMAND(glGenerateMipmap(GL_TEXTURE_2D));

			IOO_PUSH_SYNC_RENDER_COMMAND(glBindTexture(GL_TEXTURE_2D, 0));
		}
	}
}
