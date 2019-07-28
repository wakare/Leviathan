#pragma once
#include <GL/glew.h>
#include "IOpenGLObject.h"

namespace Leviathan
{
	namespace Renderer
	{
		class OpenGLTextureObject : public IOpenGLObject
		{
		public:
			OpenGLTextureObject(GLuint width, GLuint height, const GLvoid* data);
			~OpenGLTextureObject();

			GLuint GetTextureObject() const;

			void SetTextureUnitOffset(GLuint unit_offset);
			GLuint GetTextureUnitOffset() const;

			OpenGLTextureObject* ToOpenGLTextureObject() override { return this; }

		private:
			GLuint m_width;
			GLuint m_height;
			GLuint m_texture_unit_offset;
			GLuint m_texture_object;
		};
	}
}

