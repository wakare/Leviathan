#pragma once

#include <gl/glew.h>
#include "Light.h"
#include "LPtr.h"

namespace Leviathan
{
	namespace Renderer
	{
		class OpenGLLight
		{
		public:
			OpenGLLight();
			OpenGLLight(LPtr<Light> pLight);
			OpenGLLight(Eigen::Vector3f position, Eigen::Vector3f ambientColor, Eigen::Vector3f diffuseColor, Eigen::Vector3f specularColor);
			
			bool SetLightUniformVar(GLuint shaderProgram);
			bool SetLightCoord(const Eigen::Vector3f& newCoord);

		private:
			LPtr<Light> m_pLight;

			GLint m_lightPositionLocation;
			GLint m_lightAmbientLocation;
			GLint m_lightDiffuseLocation;
			GLint m_lightSpecularLocation;
		};
	}
}