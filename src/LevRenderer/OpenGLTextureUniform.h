#pragma once
#include <gl/glew.h>
#include <string>
#include "LPtr.h"
#include "IOpenGLUniform.h"

namespace Leviathan
{
	namespace Scene
	{
		class LevTextureUniform;
		class LevTextureObject;
	}

	namespace Renderer
	{
		class IOpenGLTextureObject;

		class OpenGLTextureUniform : public IOpenGLUniform
		{
		public:
			OpenGLTextureUniform(const Scene::LevTextureUniform& texture);
			~OpenGLTextureUniform();

			const std::string& GetUniformName() const override;

			bool Apply(GLuint shaderProgram) override;
			bool UnApply(GLuint shaderProgram) override;

		private:
			std::string m_texture_uniform_name;
			GLint m_texture_uniform_location;

			LPtr<IOpenGLTextureObject> m_texture_object;
		};
	}
}
