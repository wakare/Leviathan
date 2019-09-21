#pragma once
#include <GL/glew.h>
#include "IOpenGLTextureObject.h"

namespace Leviathan
{
	namespace Renderer
	{
		class OpenGLColorTexture2DObject : public IOpenGLTextureObject
		{
		public:
			~OpenGLColorTexture2DObject();

			OpenGLTextureObjectType GetTextureObjectType() const override { return EOTOT_2D_TEX; };
			OpenGLColorTexture2DObject* To2DColorTextureObject() override { return this; }

		protected:
			friend class OpenGLObjectManager;

			/*
			 * OpenGL Object resource should be created in Object manager class
			 */
			OpenGLColorTexture2DObject(OpenGLObjectManager& manager, GLuint texture_object_uid, GLuint width, GLuint height, const GLvoid* data);

			GLuint m_width;
			GLuint m_height;
		};
	}
}

