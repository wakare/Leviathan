#include "OpenGLTextureBufferObject.h"
#include "OpenGLTexture2DObject.h"
#include "OpenGLResourceManager.h"
#include "OpenGLObjectManager.h"

namespace Leviathan
{
	namespace Renderer
	{
		OpenGLTextureBufferObject::OpenGLTextureBufferObject(const Scene::LevTextureObject& texture_object)
			: m_texture_object(nullptr)
		{
			auto& object_manager = OpenGLResourceManager::Instance().GetObjectManager();

			switch (texture_object.GetTextureType())
			{
				case Scene::LevTextureType::ELTT_2D_TEXTURE:
					if (!object_manager.GetTextureResource(texture_object.GetID(), m_texture_object))
					{
						const bool created = object_manager.CreateTextureResource(texture_object.GetID(), texture_object.GetWidth(), 
							texture_object.GetHeight(), texture_object.GetTextureData(), m_texture_object);
						LEV_ASSERT(created);
					}

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
