﻿#include "OpenGLDepthTexture2DObject.h"
#include "OpenGLObjectManager.h"
#include "OpenGLResourceManager.h"

namespace Leviathan
{
	namespace Renderer
	{
		OpenGLDepthTexture2DObject::~OpenGLDepthTexture2DObject()
		{
			IOR_PUSH_SYNC_RENDER_COMMAND(glDeleteTextures(1, &m_texture_object));
		}

		OpenGLDepthTexture2DObject::OpenGLDepthTexture2DObject(OpenGLObjectManager& manager,
			GLuint texture_object_uid, GLuint width, GLuint height, const GLvoid* data) 
			: IOpenGLTextureObject(manager, texture_object_uid)
			, m_width(width)
			, m_height(height)
		{
			IOR_PUSH_SYNC_RENDER_COMMAND(glGenTextures(1, &m_texture_object));
			IOR_PUSH_SYNC_RENDER_COMMAND(glBindTexture(GL_TEXTURE_2D, m_texture_object));

			IOR_PUSH_SYNC_RENDER_COMMAND(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
			IOR_PUSH_SYNC_RENDER_COMMAND(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

			IOR_PUSH_SYNC_RENDER_COMMAND(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
			IOR_PUSH_SYNC_RENDER_COMMAND(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

			IOR_PUSH_SYNC_RENDER_COMMAND(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, m_width, m_height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, data));
			IOR_PUSH_SYNC_RENDER_COMMAND(glGenerateMipmap(GL_TEXTURE_2D));

			IOR_PUSH_SYNC_RENDER_COMMAND(glBindTexture(GL_TEXTURE_2D, 0));
		}
	}
}
