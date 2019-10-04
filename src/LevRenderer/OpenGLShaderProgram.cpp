#include "OpenGLShaderProgram.h"
#include "OpenGLNumericalUniform.h"
#include "LevRAttrShaderProgram.h"
#include "OpenGLResourceManager.h"

namespace Leviathan
{
	namespace Renderer 
	{
		OpenGLShaderProgram::OpenGLShaderProgram(OpenGLObjectManager& manager, const Scene::LevRAttrShaderProgram& shader_program)
			: IOpenGLObject(manager)
			, m_shader_program(shader_program)
			, m_bInited(false)
		{
			if (!Init())
			{
				throw "exception";
			}
		};

		bool OpenGLShaderProgram::Init()
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

		bool OpenGLShaderProgram::SetGLUniformState()
		{
			if (!m_bInited)
			{
				return false;
			}

			for (auto& uniform : m_pGLUniforms)
			{
				uniform.second->Apply(m_shaderProgram);
			}

			return true;
		}

		bool OpenGLShaderProgram::AddUniform(LSPtr<OpenGLNumericalUniform> pUniform)
		{
			if (m_pGLUniforms.find(pUniform->GetUniformName()) != m_pGLUniforms.end())
			{
				throw "GLShaderProgram::AddUniform(std::shared_ptr<GLUniform> pUniform) --> Add Uniform failed.";
				return false;
			}

			m_pGLUniforms.insert(std::make_pair(pUniform->GetUniformName(), pUniform));

			return true;
		}

		LSPtr<OpenGLNumericalUniform>& OpenGLShaderProgram::GetUniformByName(std::string uniformName)
		{
			auto findIt = m_pGLUniforms.find(uniformName);
			if (findIt == m_pGLUniforms.end())
			{
				throw "FATAL ERROR";
			}

			return findIt->second;
		}

		GLuint OpenGLShaderProgram::GetShaderProgram() const 
		{ 
			return m_shaderProgram; 
		};

		unsigned OpenGLShaderProgram::GetID() const
		{
			return m_shader_program.GetID();
		}

		bool OpenGLShaderProgram::_compileAll()
		{
			IOR_PUSH_ASYNC_RENDER_COMMAND(m_VertexShader = glCreateShader(GL_VERTEX_SHADER));
			if (!_compileShader(m_shader_program.GetShaderProgram().m_vert_shader.c_str(), m_VertexShader))
			{
				return false;
			}

			IOR_PUSH_ASYNC_RENDER_COMMAND(m_FragmentShader = glCreateShader(GL_FRAGMENT_SHADER));
			if (!_compileShader(m_shader_program.GetShaderProgram().m_frag_shader.c_str(), m_FragmentShader))
			{
				return false;
			}

			return true;
		}

		bool OpenGLShaderProgram::_linkAll()
		{
			IOR_PUSH_ASYNC_RENDER_COMMAND(m_shaderProgram = glCreateProgram());
			GLint success = GL_FALSE;
			GLchar infoLog[512];

			// Link shader program
			IOR_PUSH_ASYNC_RENDER_COMMAND(glAttachShader(m_shaderProgram, m_VertexShader));
			IOR_PUSH_ASYNC_RENDER_COMMAND(glAttachShader(m_shaderProgram, m_FragmentShader));

			IOR_PUSH_ASYNC_RENDER_COMMAND(glLinkProgram(m_shaderProgram));
			IOR_PUSH_ASYNC_RENDER_COMMAND(glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success));

			// Print Link Error
			if (!success) {
				IOR_PUSH_SYNC_RENDER_COMMAND(glGetProgramInfoLog(m_shaderProgram, 512, NULL, infoLog));
				LeviathanOutStream << "ERROR::SHADER::LINK_FAILED\n" << infoLog << std::endl;

				return false;
			}

			return true;
		}

		bool OpenGLShaderProgram::_compileShader(const char* pczShaderSource, GLuint shaderProgram)
		{
			GLint success = GL_FALSE;

			IOR_PUSH_ASYNC_RENDER_COMMAND(glShaderSource(shaderProgram, 1, &pczShaderSource, nullptr));
			IOR_PUSH_ASYNC_RENDER_COMMAND(glCompileShader(shaderProgram));
			IOR_PUSH_ASYNC_RENDER_COMMAND(glGetShaderiv(shaderProgram, GL_COMPILE_STATUS, &success));
			GLchar infoLog[512];

			// Print Compile Error
			if (success == GL_FALSE)
			{
				IOR_PUSH_SYNC_RENDER_COMMAND(glGetShaderInfoLog(shaderProgram, 512, nullptr, infoLog));
				LeviathanOutStream << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;

				return false;
			}

			return true;
		}
	}
}