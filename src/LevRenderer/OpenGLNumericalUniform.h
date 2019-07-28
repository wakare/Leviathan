#pragma once

#include <gl/glew.h>
#include "IOpenGLUniform.h"
#include "LevRAttrUniform.h"

namespace Leviathan
{
	namespace Renderer
	{
		class OpenGLNumericalUniform : public IOpenGLUniform
		{
		public:
			OpenGLNumericalUniform(const Scene::LevRAttrUniform& scene_uniform);
			const std::string& GetUniformName() const override;

			bool Apply(GLuint program) override;
			bool UnApply(GLuint program) override;

		private:
			const Scene::LevRAttrUniform& m_scene_uniform;
			GLint m_uniform_location;
		};
	}
}