#include "OpenGLColorTexture3DObject.h"

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
			glGenTextures(1, &m_texture_object);
			glBindTexture(GL_TEXTURE_3D, m_texture_object);

			glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glTexImage3D(GL_TEXTURE_3D, 0, GL_R32F, m_width, m_height, m_depth, 0, GL_RED, GL_FLOAT, data);
			glGenerateMipmap(GL_TEXTURE_3D);

			glBindTexture(GL_TEXTURE_3D, 0);
		}

		OpenGLColorTexture3DObject::~OpenGLColorTexture3DObject()
		{
			glDeleteTextures(1, &m_texture_object);
		}
	}
}