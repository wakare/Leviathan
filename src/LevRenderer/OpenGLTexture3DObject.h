﻿#pragma once

#include "IOpenGLTextureObject.h"
#include "GL/glew.h"

namespace Leviathan
{
	namespace Renderer
	{
		class OpenGLTexture3DObject : public IOpenGLTextureObject
		{
		public:
			OpenGLTexture3DObject(GLuint width, GLuint height, GLuint depth, const GLvoid* data);
			~OpenGLTexture3DObject();

			OpenGLTextureObjectType GetTextureObjectType() const override { return EOTOT_3D; };
			OpenGLTexture3DObject* To3DTextureObject() override { return this; }

		private:
			GLuint m_width;
			GLuint m_height;
			GLuint m_depth;
		};
	}
}

