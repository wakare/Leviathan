#include "OpenGLObjectManager.h"
#include "OpenGLTexture2DObject.h"
#include "OpenGLTexture3DObject.h"

namespace Leviathan
{
	namespace Renderer
	{
		OpenGLObjectManager::OpenGLObjectManager()
		= default;

		bool OpenGLObjectManager::CreateTextureResource(GLuint texture_object_uid, GLuint width, GLuint height,
			const GLvoid* data, LPtr<IOpenGLTextureObject>& out)
		{
			auto it = m_texture_objects.find(texture_object_uid);
			if (it != m_texture_objects.end())
			{
				return false;
			}

			out.Reset(new OpenGLTexture2DObject(*this, texture_object_uid, width, height, data));
			m_texture_objects[texture_object_uid] = out;
			return true;
		}

		bool OpenGLObjectManager::CreateTextureResource(GLuint texture_object_uid, GLuint width, GLuint height,
			GLuint depth, const GLvoid* data, LPtr<IOpenGLTextureObject>& out)
		{
			auto it = m_texture_objects.find(texture_object_uid);
			if (it != m_texture_objects.end())
			{
				return false;
			}

			out.Reset(new OpenGLTexture3DObject(*this, texture_object_uid, width, height, depth, data));
			m_texture_objects[texture_object_uid] = out;
			return true;
		}

		bool OpenGLObjectManager::GetTextureResource(GLuint texture_object_uid, LPtr<IOpenGLTextureObject>& out)
		{
			auto it = m_texture_objects.find(texture_object_uid);
			if (it == m_texture_objects.end())
			{
				out = nullptr;
				return false;
			}

			out = it->second;
			return true;
		}
	}
}