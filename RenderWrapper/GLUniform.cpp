#include "GLUniform.h"

GLUniform::GLUniform(const char* uniformName, UniformType type) : 
	m_uniformName(uniformName), 
	m_uniformType(type)
{

}

bool GLUniform::SetData(float* data, unsigned dataSize)
{
	// Do nothing if data has inited before
	if (_checkDataInited())
	{
		return false;
	}

	m_fUniformArray = std::make_shared<UniformArray<float>>(dataSize);
	m_fUniformArray->SetArrayData(data, dataSize);

	return true;
}

bool GLUniform::SetData(double* data, unsigned dataSize)
{
	// Do nothing if data has inited before
	if (_checkDataInited())
	{
		return false;
	}

	m_dUniformArray = std::make_shared<UniformArray<double>>(dataSize);
	m_dUniformArray->SetArrayData(data, dataSize);

	return true;
}

bool GLUniform::SetUniformVar(GLuint program)
{
	GLuint uniformLocation = glGetUniformLocation(program, m_uniformName);
	if (uniformLocation == -1)
	{
		throw "GLUniform::SetUniformVar(GLuint program) --> Get uniform location failed.";
		return false;
	}

	switch (m_uniformType)
	{
	case TYPE_FLOAT_MAT4:
		glUniformMatrix4fv(uniformLocation, 1, true, m_fUniformArray->GetArraydata());
		break;

	default:
		return false;
	}

	return true;
}

bool GLUniform::_checkDataInited()
{
	if (m_dUniformArray || m_fUniformArray)
	{
		return true;
	}

	return false;
}
