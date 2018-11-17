#include "GLShaderProgram.h"
#include <iostream>

namespace Leviathan
{
	bool GLShaderProgram::Init()
	{
		if (m_bInited)
		{
			return true;
		}

		if (!_compileAll())
		{
			return false;
		}

		if (!_linkAll())
		{
			return false;
		}

		m_bInited = true;
		return true;
	}

	bool GLShaderProgram::SetGLUniformState()
	{
		if (!m_bInited)
		{
			return false;
		}

		for (auto& uniform : m_pGLUniforms)
		{
			uniform.second->SetUniformVar(m_shaderProgram);
		}

		return true;
	}

	bool GLShaderProgram::AddUniform(LPtr<GLUniform> pUniform)
	{
		if (m_pGLUniforms.find(pUniform->GetUniformName()) != m_pGLUniforms.end())
		{
			throw "GLShaderProgram::AddUniform(std::shared_ptr<GLUniform> pUniform) --> Add Uniform failed.";
			return false;
		}

		m_pGLUniforms.insert(std::make_pair(pUniform->GetUniformName(), pUniform));
		//m_pGLUniforms[pUniform->GetUniformName()] = pUniform;
		return true;
	}

	LPtr<GLUniform> GLShaderProgram::GetUniformByName(std::string uniformName)
	{
		auto findIt = m_pGLUniforms.find(uniformName);
		if (findIt == m_pGLUniforms.end())
		{
			return nullptr;
		}

		return findIt->second;
	}

	bool GLShaderProgram::_compileAll()
	{
		m_VertexShader = glCreateShader(GL_VERTEX_SHADER);
		if (!_compileShader(m_pczVertexShader, m_VertexShader))
		{
			return false;
		}

		m_FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		if (!_compileShader(m_pczFragmentShader, m_FragmentShader))
		{
			return false;
		}

		if (m_pczGeomShader)
		{
			m_GeomShader = glCreateShader(GL_GEOMETRY_SHADER);
			if (!_compileShader(m_pczGeomShader, m_GeomShader))
			{
				return false;
			}
		}

		return true;
	}

	bool GLShaderProgram::_linkAll()
	{
		m_shaderProgram = glCreateProgram();
		GLint success = GL_FALSE;
		GLchar infoLog[512];

		// Link shader program
		glAttachShader(m_shaderProgram, m_VertexShader);
		glAttachShader(m_shaderProgram, m_FragmentShader);
		if (m_pczGeomShader)
		{
			glAttachShader(m_shaderProgram, m_GeomShader);
		}

		glLinkProgram(m_shaderProgram);
		glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success);

		// Print Link Error
		if (!success) {
			glGetProgramInfoLog(m_shaderProgram, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::LINK_FAILED\n" << infoLog << std::endl;
		}

		return true;
	}

	bool GLShaderProgram::_compileShader(const GLchar* const* pczShaderSource, GLuint shaderProgram)
	{
		GLint success = GL_FALSE;

		glShaderSource(shaderProgram, 1, pczShaderSource, nullptr);
		glCompileShader(shaderProgram);
		glGetShaderiv(shaderProgram, GL_COMPILE_STATUS, &success);
		GLchar infoLog[512];

		// Print Compile Error
		if (success == GL_FALSE)
		{
			glGetShaderInfoLog(shaderProgram, 512, nullptr, infoLog);
			std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;

			return false;
		}

		return true;
	}
}