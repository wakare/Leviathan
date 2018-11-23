#include "CommonGLMaterial.h"
#include "GlobalDef.h"

Leviathan::CommonGLMaterial::CommonGLMaterial(GLColor ambient /*= { 0.0f, 0.0f, 0.0f }*/, GLColor diffuse /*= { 0.0f, 0.0f, 0.0f }*/, GLColor specular /*= { 0.0f, 0.0f, 0.0f }*/, float fShininess /*= 32.0f*/) :
	m_CAmbient(ambient),
	m_CDiffuse(diffuse),
	m_CSpecular(specular),
	m_fShininess(fShininess)
{

}

bool Leviathan::CommonGLMaterial::SetMaterial(GLuint fragmentProgram)
{
	GLint nErrorCode = -1;

	GLint matAmbientLocation = glGetUniformLocation(fragmentProgram, "material.ambient");
	GLint matDiffuseLocation = glGetUniformLocation(fragmentProgram, "material.diffuse");
	GLint matSpecularLocation = glGetUniformLocation(fragmentProgram, "material.specular");
	GLint matShininessLocation = glGetUniformLocation(fragmentProgram, "material.shininess");

	if (matAmbientLocation == nErrorCode || 
		matDiffuseLocation == nErrorCode ||
		matSpecularLocation == nErrorCode || 
		matShininessLocation == nErrorCode)
	{
		LeviathanOutStream << "[ERROR] Get uniform var failed." << std::endl;
		return false;
	}

	glUniform3f(matAmbientLocation, m_CAmbient.r, m_CAmbient.g, m_CAmbient.b);
	glUniform3f(matDiffuseLocation, m_CDiffuse.r, m_CDiffuse.g, m_CDiffuse.b);
	glUniform3f(matSpecularLocation, m_CSpecular.r, m_CSpecular.g, m_CSpecular.b);
	glUniform1f(matShininessLocation, m_fShininess);

	return true;
}
