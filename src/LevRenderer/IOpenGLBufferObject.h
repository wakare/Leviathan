#pragma once

namespace Leviathan
{
	namespace Renderer
	{
		enum OpenGLBufferBufferType
		{
			EOBBT_TEXTURE_BUFFER_OBJECT
		};

		class OpenGLTextureBufferObject;
		class OpenGLObjectManager;

		class IOpenGLBufferObject
		{
		public:
			IOpenGLBufferObject(OpenGLObjectManager& manager)
				: m_manager(manager)
			{
				
			}

			virtual ~IOpenGLBufferObject() = default;
			virtual OpenGLBufferBufferType GetBufferObjectType() const = 0;
			virtual OpenGLTextureBufferObject* ToTextureBufferObject() { return nullptr; }

		protected:
			OpenGLObjectManager& m_manager;
		};
	}
}


