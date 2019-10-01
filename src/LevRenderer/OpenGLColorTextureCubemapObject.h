#pragma once

#include "IOpenGLTextureObject.h"

namespace Leviathan
{
	namespace Renderer
	{
		class OpenGLColorTextureCubemapObject : public IOpenGLTextureObject
		{
		public:

			OpenGLTextureObjectType GetTextureObjectType() const override { return EOTOT_CUBEMAP_TEX; };
			OpenGLColorTextureCubemapObject* ToTextureCubemapColorObject() override { return this; }

		protected:
			friend class OpenGLObjectManager;
			/*
			 * OpenGL Object resource should be created in Object manager class
			 */
			OpenGLColorTextureCubemapObject(OpenGLObjectManager& manager, GLuint texture_object_uid, GLuint width, GLuint height, const GLvoid** cubemap_data);

			GLuint m_width;
			GLuint m_height;
		};
	}
}


