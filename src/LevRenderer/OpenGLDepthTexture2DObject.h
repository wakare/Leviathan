#pragma once
#include "IOpenGLTextureObject.h"
#include <gl/glew.h>

namespace Leviathan
{
	namespace Renderer
	{
		class OpenGLDepthTexture2DObject : public IOpenGLTextureObject
		{
		public:
			~OpenGLDepthTexture2DObject();

			OpenGLTextureObjectType GetTextureObjectType() const override { return EOTOT_2D_TEX; };
			OpenGLDepthTexture2DObject* To2DDepthTextureObject() override { return this; }

		protected:
			friend class OpenGLObjectManager;

			/*
			 * OpenGL Object resource should be created in Object manager class
			 */
			OpenGLDepthTexture2DObject(OpenGLObjectManager& manager, GLuint texture_object_uid, GLuint width, GLuint height, const GLvoid* data);

			GLuint m_width;
			GLuint m_height;
		};
	}
}

