#include "OpenGLTextureBufferObject.h"
#include "OpenGLColorTexture2DObject.h"
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

			if (!object_manager.GetTextureResource(texture_object.GetID(), m_texture_object))
			{
				const bool created = object_manager.CreateTextureResource(texture_object.GetTextureType(), texture_object.GetID(), texture_object.GetWidth(),
									texture_object.GetHeight(), texture_object.GetDepth(), texture_object.GetTextureData(), m_texture_object);
				LEV_ASSERT(created);
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
