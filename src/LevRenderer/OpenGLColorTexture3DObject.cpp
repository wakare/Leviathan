#include "OpenGLColorTexture3DObject.h"
#include "OpenGLObjectManager.h"
#include "OpenGLResourceManager.h"

namespace Leviathan
{
	namespace Renderer
	{
		OpenGLColorTexture3DObject::OpenGLColorTexture3DObject(OpenGLObjectManager& manager, GLuint texture_object_uid, GLuint width, GLuint height, GLuint depth, const GLvoid* data)
			: IOpenGLTextureObject(manager, texture_object_uid)
			, m_width(width)
			, m_height(height)
			, m_depth(depth)
		{
			IOR_PUSH_SYNC_RENDER_COMMAND(glGenTextures(1, &m_texture_object));
			IOR_PUSH_SYNC_RENDER_COMMAND(glBindTexture(GL_TEXTURE_3D, m_texture_object));

			IOR_PUSH_SYNC_RENDER_COMMAND(glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT));
			IOR_PUSH_SYNC_RENDER_COMMAND(glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT));

			IOR_PUSH_SYNC_RENDER_COMMAND(glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
			IOR_PUSH_SYNC_RENDER_COMMAND(glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

			IOR_PUSH_SYNC_RENDER_COMMAND(glTexImage3D(GL_TEXTURE_3D, 0, GL_R32F, m_width, m_height, m_depth, 0, GL_RED, GL_FLOAT, data));
			IOR_PUSH_SYNC_RENDER_COMMAND(glGenerateMipmap(GL_TEXTURE_3D));

			IOR_PUSH_SYNC_RENDER_COMMAND(glBindTexture(GL_TEXTURE_3D, 0));
		}

		OpenGLColorTexture3DObject::~OpenGLColorTexture3DObject()
		{
			IOR_PUSH_SYNC_RENDER_COMMAND(glDeleteTextures(1, &m_texture_object));
		}
	}
}
