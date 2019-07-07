#pragma once

#include <gl/glew.h>
#include "LPtr.h"
#include "LevRAttrUniform.h"

namespace Leviathan
{
	namespace Renderer
	{
		class OpenGLUniform
		{
		public:
			OpenGLUniform(const Scene::LevRAttrUniform& scene_uniform);
			const std::string& GetUniformName() const;
			
			bool Apply(GLuint program);

		private:
			const Scene::LevRAttrUniform& m_scene_uniform;
		};
	}
}