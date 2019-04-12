#include "OpenGLPointLight.h"
#include "LevPointLight.h"

namespace Leviathan
{
	namespace Renderer
	{
		OpenGLPointLight::OpenGLPointLight(const Scene::LevPointLight& light) :
			m_light(light),
			m_lightPositionLocation(-1),
			m_lightAmbientLocation(-1),
			m_lightDiffuseLocation(-1),
			m_lightSpecularLocation(-1)
		{
		}

		bool OpenGLPointLight::SetLightUniformVar(GLuint shaderProgram)
		{
			if (m_lightPositionLocation < 0)
			{
				m_lightPositionLocation = glGetUniformLocation(shaderProgram, "light.position");
				if (m_lightPositionLocation == -1)
				{
					LeviathanOutStream << "[ERROR] Get light position uniform location failed." << std::endl;
					//return false;
				}
			}

			glUniform3f(m_lightPositionLocation, m_light.LightCoordination().x(), m_light.LightCoordination().y(), m_light.LightCoordination().z());

			if (m_lightAmbientLocation < 0)
			{
				m_lightAmbientLocation = glGetUniformLocation(shaderProgram, "light.ambient");
				if (m_lightAmbientLocation == -1)
				{
					LeviathanOutStream << "[ERROR] Get light position ambient color location failed." << std::endl;
					//return false;
				}
			}

			glUniform3f(m_lightAmbientLocation, m_light.AmbientColor().x(), m_light.AmbientColor().y(), m_light.AmbientColor().z());

			if (m_lightDiffuseLocation < 0)
			{
				m_lightDiffuseLocation = glGetUniformLocation(shaderProgram, "light.diffuse");
				if (m_lightDiffuseLocation == -1)
				{
					LeviathanOutStream << "[ERROR] Get light position diffuse color location failed." << std::endl;
					//return false;
				}
			}

			glUniform3f(m_lightDiffuseLocation, m_light.DiffuseColor().x(), m_light.DiffuseColor().y(), m_light.DiffuseColor().z());

			if (m_lightSpecularLocation < 0)
			{
				m_lightSpecularLocation = glGetUniformLocation(shaderProgram, "light.specular");
				if (m_lightSpecularLocation == -1)
				{
					LeviathanOutStream << "[ERROR] Get light position specular color location failed." << std::endl;
					//return false;
				}
			}

			glUniform3f(m_lightSpecularLocation, m_light.SpecularColor().x(), m_light.SpecularColor().y(), m_light.SpecularColor().z());
			return true;
		}
	}
}