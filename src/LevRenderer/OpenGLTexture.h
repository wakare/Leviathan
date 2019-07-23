#pragma once
#include <gl/glew.h>
#include <LevTextureObject.h>

namespace Leviathan
{
	namespace Renderer
	{
		class OpenGLTexture
		{
		public:
			OpenGLTexture(const Scene::LevTextureObject& texture);
			~OpenGLTexture();

			GLboolean ApplyTexture(GLuint shaderProgram, const char* samplerUniformName, GLuint textureUnitOffset = 0);
			GLboolean UnApplyTexture(GLuint shaderProgram, GLuint textureUnitOffset = 0);

		private:
			std::string m_texture_uniform_name;
			GLint m_texture_uniform_location;

			GLuint m_textureHandle;
			GLuint m_uWidth;
			GLuint m_uHeight;
		};
	}
}