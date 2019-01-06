#include "GLCommonMaterial.h"
#include "GlobalDef.h"

Leviathan::GLCommonMaterial::GLCommonMaterial(Color ambient /*= { 0.0f, 0.0f, 0.0f }*/, Color diffuse /*= { 0.0f, 0.0f, 0.0f }*/, Color specular /*= { 0.0f, 0.0f, 0.0f }*/, float fShininess /*= 32.0f*/) :
	m_CAmbient(ambient),
	m_CDiffuse(diffuse),
	m_CSpecular(specular),
	m_fShininess(fShininess),
	m_uMaxTexture2DCount(16)
{

}

bool Leviathan::GLCommonMaterial::ApplyMaterial(GLuint program)
{
	GLint nErrorCode = -1;

	GLint nAmbientLocation = glGetUniformLocation(program, "material.ambient");
	GLint nDiffuseLocation = glGetUniformLocation(program, "material.diffuse");
	GLint nSpecularLocation = glGetUniformLocation(program, "material.specular");
	GLint nShininessLocation = glGetUniformLocation(program, "material.shininess");

	if (nAmbientLocation == nErrorCode &&
		nDiffuseLocation == nErrorCode &&
		nSpecularLocation == nErrorCode && 
		nShininessLocation == nErrorCode)
	{
		LeviathanOutStream << "[ERROR] Get material uniform failed." << std::endl;
		return false;
	}

	glUniform3f(nAmbientLocation, m_CAmbient.r, m_CAmbient.g, m_CAmbient.b);
	glUniform3f(nDiffuseLocation, m_CDiffuse.r, m_CDiffuse.g, m_CDiffuse.b);
	glUniform3f(nSpecularLocation, m_CSpecular.r, m_CSpecular.g, m_CSpecular.b);
	glUniform1f(nShininessLocation, m_fShininess);

	for (unsigned i = 0; i < m_pTexture2DVec.size(); i++)
	{
		if (m_pTexture2DVec[i]->ApplyTexture(i, program, "outTexture" + i))
		{
			LeviathanOutStream << "[WARN] Apply texture failed." << std::endl;
			return false;
		}
	}

	return true;
}

bool Leviathan::GLCommonMaterial::UnApplyMaterial(GLuint program)
{
	for (unsigned i = 0; i < m_pTexture2DVec.size(); i++)
	{
		if (m_pTexture2DVec[i]->UnApplyTexture(i, program))
		{
			LeviathanOutStream << "[WARN] UnApply texture failed." << std::endl;
			return false;
		}
	}

	return true;
}

bool Leviathan::GLCommonMaterial::AddTexture2D(LPtr<GLTexture2D> pTexture2D)
{
	if (m_pTexture2DVec.size() >= m_uMaxTexture2DCount)
	{
		LeviathanOutStream << "[WARN] Arrive max texture unit count." << std::endl;
		return false;
	}

	m_pTexture2DVec.push_back(pTexture2D);
	return true;
}
