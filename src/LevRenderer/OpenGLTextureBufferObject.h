#pragma once

#include "IOpenGLBufferObject.h"
#include "LevTextureObject.h"
#include "IOpenGLTextureObject.h"

namespace Leviathan
{
	namespace Renderer
	{
		class OpenGLTextureBufferObject : public IOpenGLBufferObject
		{
		public:
			OpenGLTextureBufferObject(const Scene::LevTextureObject& texture_object);

			OpenGLBufferBufferType GetBufferObjectType() const override;
			OpenGLTextureBufferObject* ToTextureBufferObject() override;

			GLuint GetTextureObject();

		private:
			LSPtr<IOpenGLTextureObject> m_texture_object;
		};
	}
}


