#include "OpenGLTextureBufferObject.h"
#include "OpenGLTexture2DObject.h"
#include "OpenGLResourceManager.h"

namespace Leviathan
{
	namespace Renderer
	{
		OpenGLTextureBufferObject::OpenGLTextureBufferObject(const Scene::LevTextureObject& texture_object)
			: m_texture_object(nullptr)
		{
			switch (texture_object.GetTextureType())
			{
				case Scene::LevTextureType::ELTT_2D_TEXTURE:
					m_texture_object.Reset(new OpenGLTexture2DObject(OpenGLResourceManager::Instance().GetObjectManager(), texture_object.GetWidth(), texture_object.GetHeight(), texture_object.GetTextureData()));
					break;

				default:
					LogLine("[WARN] Init texture object with type: " << texture_object.GetTextureType());
					break;
			}
		}

		OpenGLBufferBufferType OpenGLTextureBufferObject::GetBufferObjectType() const
		{
			return EOBBT_TEXTURE_BUFFER_OBJECT;
		}

		OpenGLTextureBufferObject* OpenGLTextureBufferObject::ToTextureBufferObject()
		{
			return this;
		}

		GLuint OpenGLTextureBufferObject::GetTextureObject()
		{
			return m_texture_object->GetTextureObject();
		}
	}
}
