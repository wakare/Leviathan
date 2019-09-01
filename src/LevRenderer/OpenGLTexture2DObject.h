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
			OpenGLTexture2DObject(OpenGLObjectManager& manager, GLuint width, GLuint height, const GLvoid* data);
			~OpenGLTexture2DObject();

			OpenGLTextureObjectType GetTextureObjectType() const override { return EOTOT_2D; };
			OpenGLTexture2DObject* To2DTextureObject() override { return this; }

		protected:
			bool Register() override;

			GLuint m_width;
			GLuint m_height;
		};
	}
}

