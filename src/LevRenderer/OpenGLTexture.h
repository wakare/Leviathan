#pragma once
#include <gl/glew.h>

namespace Leviathan
{
	namespace Renderer
	{
		class OpenGLTexture
		{
		public:
			OpenGLTexture(unsigned char* pData, unsigned uWidth, unsigned uHeight);
			GLboolean ApplyTexture(GLuint textureUnitOffset, GLuint shaderProgram, const char* samplerUniformName);
			GLboolean UnApplyTexture(GLuint textureUnitOffset, GLuint shaderProgram);

		private:
			GLuint m_textureHandle;
			GLuint m_uWidth;
			GLuint m_uHeight;
		};
	}
}