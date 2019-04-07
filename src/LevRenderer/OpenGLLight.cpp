#include "OpenGLLight.h"

namespace Leviathan
{
	namespace Renderer
	{

		OpenGLLight::OpenGLLight() :
			m_pLight(nullptr),
			m_lightPositionLocation(-1),
			m_lightAmbientLocation(-1),
			m_lightDiffuseLocation(-1),
			m_lightSpecularLocation(-1)
		{

		}

		OpenGLLight::OpenGLLight(Eigen::Vector3f position, Eigen::Vector3f ambientColor, Eigen::Vector3f diffuseColor, Eigen::Vector3f specularColor) :
			OpenGLLight()
		{
			m_pLight = new Light(position, ambientColor, diffuseColor, specularColor);
		};

		OpenGLLight::OpenGLLight(LPtr<Light> pLight) :
			OpenGLLight()
		{
			m_pLight = pLight;
		}

		bool OpenGLLight::SetLightUniformVar(GLuint shaderProgram)
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

			glUniform3f(m_lightPositionLocation, m_pLight->m_lightCoordination.x(), m_pLight->m_lightCoordination.y(), m_pLight->m_lightCoordination.z());

			if (m_lightAmbientLocation < 0)
			{
				m_lightAmbientLocation = glGetUniformLocation(shaderProgram, "light.ambient");
				if (m_lightAmbientLocation == -1)
				{
					LeviathanOutStream << "[ERROR] Get light position ambient color location failed." << std::endl;
					//return false;
				}
			}

			glUniform3f(m_lightAmbientLocation, m_pLight->m_ambientColor.x(), m_pLight->m_ambientColor.y(), m_pLight->m_ambientColor.z());

			if (m_lightDiffuseLocation < 0)
			{
				m_lightDiffuseLocation = glGetUniformLocation(shaderProgram, "light.diffuse");
				if (m_lightDiffuseLocation == -1)
				{
					LeviathanOutStream << "[ERROR] Get light position diffuse color location failed." << std::endl;
					//return false;
				}
			}

			glUniform3f(m_lightDiffuseLocation, m_pLight->m_diffuseColor.x(), m_pLight->m_diffuseColor.y(), m_pLight->m_diffuseColor.z());

			if (m_lightSpecularLocation < 0)
			{
				m_lightSpecularLocation = glGetUniformLocation(shaderProgram, "light.specular");
				if (m_lightSpecularLocation == -1)
				{
					LeviathanOutStream << "[ERROR] Get light position specular color location failed." << std::endl;
					//return false;
				}
			}

			glUniform3f(m_lightSpecularLocation, m_pLight->m_specularColor.x(), m_pLight->m_specularColor.y(), m_pLight->m_specularColor.z());
			return true;
		}

		bool OpenGLLight::SetLightCoord(const Eigen::Vector3f& newCoord)
		{
			m_pLight->SetLightCoord(newCoord);
			return true;
		}
	}
}