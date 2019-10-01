#include "OpenGLObjectManager.h"
#include "OpenGLColorTexture2DObject.h"
#include "OpenGLColorTexture3DObject.h"
#include "OpenGLDepthTexture2DObject.h"
#include "OpenGLColorTextureCubemapObject.h"

namespace Leviathan
{
	namespace Renderer
	{
		OpenGLObjectManager::OpenGLObjectManager()
		= default;

		/*bool OpenGLObjectManager::CreateTextureResource(Scene::LevTextureType tex_type, GLuint texture_object_uid, GLuint width, GLuint height,
			const GLvoid* data, LSPtr<IOpenGLTextureObject>& out)
		{
			auto it = m_texture_objects.find(texture_object_uid);
			if (it != m_texture_objects.end())
			{
				return false;
			}

			out.Reset(new OpenGLColorTexture2DObject(*this, texture_object_uid, width, height, data));
			m_texture_objects[texture_object_uid] = out;
			return true;
		}*/

		bool OpenGLObjectManager::CreateTextureResource(Scene::LevTextureType tex_type, GLuint texture_object_uid, GLuint width, GLuint height,
			GLuint depth, const GLvoid* data, LSPtr<IOpenGLTextureObject>& out)
		{
			auto it = m_texture_objects.find(texture_object_uid);
			if (it != m_texture_objects.end())
			{
				return false;
			}

			switch (tex_type)
			{
			case Scene::LevTextureType::ELTT_2D_COLOR_TEXTURE:
				{
				out.Reset(new OpenGLColorTexture2DObject(*this, texture_object_uid, width, height, data));
				break;
				}

			case Scene::LevTextureType::ELTT_2D_DEPTH_TEXTURE:
				{
				out.Reset(new OpenGLDepthTexture2DObject(*this, texture_object_uid, width, height, data));
				break;
				}

			case Scene::LevTextureType::ELTT_3D_COLOR_TEXTURE:
				{
				out.Reset(new OpenGLColorTexture3DObject(*this, texture_object_uid, width, height, depth, data));
				break;
				}

			case Scene::LevTextureType::ELTT_CUBEMAP_COLOR_TEXTURE:
				{
				out.Reset(new OpenGLColorTextureCubemapObject(*this, texture_object_uid, width, height, (const GLvoid**)(data)));
				break;
				}

			default:
				LEV_ASSERT(false);
				return false;
 			}

			m_texture_objects[texture_object_uid] = out;
			return true;
		}

		bool OpenGLObjectManager::GetTextureResource(GLuint texture_object_uid, LSPtr<IOpenGLTextureObject>& out)
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
