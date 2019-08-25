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

		class IOpenGLBufferObject
		{
		public:
			virtual OpenGLBufferBufferType GetBufferObjectType() const = 0;
			virtual OpenGLTextureBufferObject* ToTextureBufferObject() { return nullptr; }
		};
	}
}


