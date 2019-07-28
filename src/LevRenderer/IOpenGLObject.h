#pragma once
#include "IOpenGLResource.h"

namespace Leviathan
{
	namespace Renderer
	{
		class OpenGLTextureObject;

		class IOpenGLObject : public Renderer::IOpenGLResource
		{
		public:
			virtual ~IOpenGLObject() = default;

			IOpenGLObject* ToOpenGLObject() override { return this; };

			virtual OpenGLTextureObject* ToOpenGLTextureObject() { return nullptr; };
		};
	}
}
