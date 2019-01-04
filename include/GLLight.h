#pragma once

#include <GL/glew.h>
#include "BaseMath.h"
#include "GlobalDef.h"

namespace Leviathan
{
	class GLLight
	{
	public:
		GLLight(Vector3f position, Vector3f ambientColor, Vector3f diffuseColor, Vector3f specularColor) :
			m_lightCoordination(position),
			m_ambientColor(ambientColor),
			m_diffuseColor(diffuseColor),
			m_specularColor(specularColor),
			m_lightPositionLocation(-1),
			m_lightAmbientLocation(-1),
			m_lightDiffuseLocation(-1),
			m_lightSpecularLocation(-1)
		{

		};

		bool SetLightUniformVar(GLuint shaderProgram)
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

			glUniform3f(m_lightPositionLocation, m_lightCoordination.x, m_lightCoordination.y, m_lightCoordination.z);
			
			if (m_lightAmbientLocation < 0)
			{
				GLint m_lightAmbientLocation = glGetUniformLocation(shaderProgram, "light.ambient");
				if (m_lightAmbientLocation == -1)
				{
					LeviathanOutStream << "[ERROR] Get light position ambient color location failed." << std::endl;
					//return false;
				}
			}

			glUniform3f(m_lightAmbientLocation, m_ambientColor.x, m_ambientColor.y, m_ambientColor.z);

			if (m_lightDiffuseLocation)
			{
				GLint m_lightDiffuseLocation = glGetUniformLocation(shaderProgram, "light.diffuse");
				if (m_lightDiffuseLocation == -1)
				{
					LeviathanOutStream << "[ERROR] Get light position diffuse color location failed." << std::endl;
					//return false;
				}
			}

			glUniform3f(m_lightDiffuseLocation, m_diffuseColor.x, m_diffuseColor.y, m_diffuseColor.z);

			if (m_lightSpecularLocation)
			{
				GLint m_lightSpecularLocation = glGetUniformLocation(shaderProgram, "light.specular");
				if (m_lightSpecularLocation == -1)
				{
					LeviathanOutStream << "[ERROR] Get light position specular color location failed." << std::endl;
					//return false;
				}
			}

			glUniform3f(m_lightSpecularLocation, m_specularColor.x, m_specularColor.y, m_specularColor.z);

			return true;
		}

		bool SetLightCoord(const Vector3f& newCoord)
		{
			m_lightCoordination = newCoord;

			return true;
		}

	private:
		GLint m_lightPositionLocation;
		GLint m_lightAmbientLocation;
		GLint m_lightDiffuseLocation;
		GLint m_lightSpecularLocation;

		Vector3f m_lightCoordination;
		Vector3f m_ambientColor;
		Vector3f m_diffuseColor;
		Vector3f m_specularColor;
	};
}