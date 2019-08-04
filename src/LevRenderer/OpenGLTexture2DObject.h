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
			OpenGLTexture2DObject(GLuint width, GLuint height, const GLvoid* data);
			~OpenGLTexture2DObject();

			OpenGLTextureObjectType GetTextureObjectType() const override { return EOTOT_2D; };
			OpenGLTexture2DObject* To2DTextureObject() override { return this; }

		private:
			GLuint m_width;
			GLuint m_height;
		};
	}
}

