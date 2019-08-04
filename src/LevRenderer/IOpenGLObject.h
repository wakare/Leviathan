#pragma once
#include "IOpenGLResource.h"

namespace Leviathan
{
	namespace Renderer
	{
		class IOpenGLTextureObject;

		class IOpenGLObject : public Renderer::IOpenGLResource
		{
		public:
			virtual ~IOpenGLObject() = default;

			IOpenGLObject* ToOpenGLObject() override { return this; };
			virtual IOpenGLTextureObject* ToOpenGLTextureObject() { return nullptr; };
		};
	}
}
