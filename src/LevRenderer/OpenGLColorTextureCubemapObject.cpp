#include "OpenGLColorTextureCubemapObject.h"

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
			glGenTextures(1, &m_texture_object);
			glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture_object);

			for (unsigned i = 0; i < 6; ++i)
			{
				const GLvoid* single_cube_map_data = cubemap_data[i];
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, m_width, m_height,  0, GL_RGB, GL_UNSIGNED_BYTE, single_cube_map_data);
			}

			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

			glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
		}
	}
}