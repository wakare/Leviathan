#include "OpenGLColorTextureCubemapObject.h"
#include "OpenGLObjectManager.h"
#include "OpenGLRenderBackend.h"
#include "OpenGLResourceManager.h"

namespace Leviathan
{
	namespace Renderer
	{
		OpenGLColorTextureCubemapObject::OpenGLColorTextureCubemapObject(OpenGLObjectManager& manager, GLuint texture_object_uid, GLuint width,
			GLuint height, const GLvoid** cubemap_data)
			: IOpenGLTextureObject(manager, texture_object_uid)
			, m_width(width)
			, m_height(height)
		{
			IOR_PUSH_SYNC_RENDER_COMMAND(glGenTextures(1, &m_texture_object););
			IOR_PUSH_SYNC_RENDER_COMMAND(glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture_object););

			for (unsigned i = 0; i < 6; ++i)
			{
				const GLvoid* single_cube_map_data = cubemap_data[i];
				IOR_PUSH_SYNC_RENDER_COMMAND(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, single_cube_map_data););
			}

			IOR_FLUSH_RENDER_COMMAND();

			IOR_PUSH_SYNC_RENDER_COMMAND(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR););
			IOR_PUSH_SYNC_RENDER_COMMAND(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR););
			IOR_PUSH_SYNC_RENDER_COMMAND(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE););
			IOR_PUSH_SYNC_RENDER_COMMAND(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE););
			IOR_PUSH_SYNC_RENDER_COMMAND(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE););
			IOR_PUSH_SYNC_RENDER_COMMAND(glBindTexture(GL_TEXTURE_CUBE_MAP, 0););
		}
	}
}
