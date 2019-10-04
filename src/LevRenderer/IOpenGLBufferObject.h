#pragma once
#include "IOpenGLObject.h"

namespace Leviathan
{
	namespace Renderer
	{
		enum OpenGLBufferBufferType
		{
			EOBBT_TEXTURE_BUFFER_OBJECT,
			EOBBT_FRAME_BUFFER_OBJECT,
		};

		class OpenGLTextureBufferObject;
		class OpenGLObjectManager;

		class IOpenGLBufferObject : public IOpenGLObject
		{
		public:
			IOpenGLBufferObject(OpenGLObjectManager& manager)
				: IOpenGLObject(manager)
			{
				
			}

			virtual ~IOpenGLBufferObject() = default;
			virtual OpenGLBufferBufferType GetBufferObjectType() const = 0;
			virtual OpenGLTextureBufferObject* ToTextureBufferObject() { return nullptr; }
		};
	}
}


