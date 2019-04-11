#pragma once

#include "OpenGLLight.h"
#include "LPtr.h"

namespace Leviathan
{
	namespace Scene
	{
		class LevLight;
	}

	namespace Renderer
	{
		class OpenGLPointLight : public OpenGLLight
		{
		public:
			OpenGLPointLight(const Scene::LevLight& light);
			
			bool SetLightUniformVar(GLuint shaderProgram);

		private:
			const Scene::LevLight& m_light;

			GLint m_lightPositionLocation;
			GLint m_lightAmbientLocation;
			GLint m_lightDiffuseLocation;
			GLint m_lightSpecularLocation;
		};
	}
}