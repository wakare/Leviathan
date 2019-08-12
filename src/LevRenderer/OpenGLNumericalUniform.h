#pragma once

#include <gl/glew.h>
#include "IOpenGLUniform.h"
#include "LevRAttrNumericalUniform.h"

namespace Leviathan
{
	namespace Renderer
	{
		class OpenGLNumericalUniform : public IOpenGLUniform
		{
		public:
			OpenGLNumericalUniform(const Scene::LevRAttrNumericalUniform& scene_uniform);
			const std::string& GetUniformName() const override;

			bool Apply(GLuint program) override;
			bool UnApply(GLuint program) override;

		private:
			const Scene::LevRAttrNumericalUniform& m_scene_uniform;
			GLint m_uniform_location;
		};
	}
}