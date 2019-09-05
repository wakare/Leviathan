#pragma once
#include <GL/glew.h>
#include "IOpenGLTextureObject.h"

namespace Leviathan
{
	namespace Renderer
	{
		class OpenGLTexture2DObject : public IOpenGLTextureObject
		{
		public:
			~OpenGLTexture2DObject();

			OpenGLTextureObjectType GetTextureObjectType() const override { return EOTOT_2D; };
			OpenGLTexture2DObject* To2DTextureObject() override { return this; }

		protected:
			friend class OpenGLObjectManager;

			/*
			 * OpenGL Object resource should be created in Object manager class
			 */
			OpenGLTexture2DObject(OpenGLObjectManager& manager, GLuint texture_object_uid, GLuint width, GLuint height, const GLvoid* data);

			GLuint m_width;
			GLuint m_height;
		};
	}
}

