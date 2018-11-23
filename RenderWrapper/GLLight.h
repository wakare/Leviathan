#pragma once
#include "BaseMath.h"
#include "GL/glew.h"
#include "GlobalDef.h"

class GLLight
{
public:
	GLLight(Vector3f position, Vector3f ambientColor, Vector3f diffuseColor, Vector3f specularColor):
		m_lightPosition(position),
		m_ambientColor(ambientColor),
		m_diffuseColor(diffuseColor),
		m_specularColor(specularColor)
	{

	};

	bool SetLightUniformVar(GLuint shaderProgram)
	{
		GLint lightPosLocation = glGetUniformLocation(shaderProgram, "light.position");
		if (lightPosLocation == -1)
		{
			LeviathanOutStream << "[ERROR] Get light position uniform location failed." << std::endl;
			return false;
		} 
		glUniform3f(lightPosLocation, m_lightPosition.x, m_lightPosition.y, m_lightPosition.z);

		GLint lightAmbientColorLocation = glGetUniformLocation(shaderProgram, "light.ambient");
		if (lightAmbientColorLocation == -1)
		{
			LeviathanOutStream << "[ERROR] Get light position ambient color location failed." << std::endl;
			return false;
		}

		glUniform3f(lightAmbientColorLocation, m_ambientColor.x, m_ambientColor.y, m_ambientColor.z);
		
		GLint lightDiffuseColorLocation = glGetUniformLocation(shaderProgram, "light.diffuse");
		if (lightDiffuseColorLocation == -1)
		{
			LeviathanOutStream << "[ERROR] Get light position diffuse color location failed." << std::endl;
			return false;
		}

		glUniform3f(glGetUniformLocation(shaderProgram, "light.diffuse"), m_diffuseColor.x, m_diffuseColor.y, m_diffuseColor.z);
		
		GLint lightSpecularColorLocation = glGetUniformLocation(shaderProgram, "light.specular");
		if (lightSpecularColorLocation == -1)
		{
			LeviathanOutStream << "[ERROR] Get light position specular color location failed." << std::endl;
			return false;
		}

		glUniform3f(lightSpecularColorLocation, m_specularColor.x, m_specularColor.y, m_specularColor.z);
	
		return true;
	}

private:
	Vector3f m_lightPosition;
	Vector3f m_ambientColor;
	Vector3f m_diffuseColor;
	Vector3f m_specularColor;
};