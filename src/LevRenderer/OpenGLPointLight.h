#pragma once

#include "OpenGLLight.h"
#include "LPtr.h"

namespace Leviathan
{
	namespace Scene
	{
		class LevPointLight;
	}

	namespace Renderer
	{
		class OpenGLPointLight : public OpenGLLight
		{
		public:
			OpenGLPointLight(const Scene::LevPointLight& light);
			
			bool SetLightUniformVar(GLuint shaderProgram);

		private:
			const Scene::LevPointLight& m_light;

			GLint m_lightPositionLocation;
			GLint m_lightAmbientLocation;
			GLint m_lightDiffuseLocation;
			GLint m_lightSpecularLocation;
		};
	}
}