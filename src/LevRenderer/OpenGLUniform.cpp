#include "OpenGLUniform.h"

namespace Leviathan
{
	namespace Renderer
	{
		OpenGLUniform::OpenGLUniform(const char* uniformName, UniformType type) :
			m_uniformName(uniformName),
			m_uniformType(type),
			m_fUniformArray(nullptr),
			m_dUniformArray(nullptr)
		{

		}

		std::string OpenGLUniform::GetUniformName() const
		{
			return m_uniformName;
		}

		bool OpenGLUniform::SetData(const float* data, unsigned dataCount)
		{
			unsigned dataSize = dataCount * sizeof(float);

			// Do nothing if data has inited before
			if (!_checkDataInited())
			{
				m_fUniformArray = new UniformArray<float>(dataSize);
			}

			m_fUniformArray->SetArrayData(data, dataSize);

			return true;
		}

		bool OpenGLUniform::SetData(const double* data, unsigned dataSize)
		{
			// Do nothing if data has inited before
			if (_checkDataInited())
			{
				return false;
			}

			m_dUniformArray = new UniformArray<double>(dataSize);
			m_dUniformArray->SetArrayData(data, dataSize);

			return true;
		}

		bool OpenGLUniform::SetData(bool data)
		{
			m_boolData = data;
			return true;
		}

		bool OpenGLUniform::SetData(int data)
		{
			m_intData = data;
			return true;
		}

		bool OpenGLUniform::SetData(unsigned data)
		{
			m_uintData = data;
			return true;
		}

		bool OpenGLUniform::Apply(GLuint program)
		{
			GLint uniformLocation = glGetUniformLocation(program, m_uniformName.c_str());
			if (uniformLocation == -1)
			{
				throw "OpenGLUniform::Apply(GLuint program) --> Get uniform location failed.";
				return false;
			}

			switch (m_uniformType)
			{
			case TYPE_FLOAT_MAT4:
			{
				glUniformMatrix4fv(uniformLocation, 1, false, m_fUniformArray->GetArraydata());
				break;
			}	

			case TYPE_FLOAT_VEC3:
			{
				auto* floatLocation = m_fUniformArray->GetArraydata();
				glUniform3f(uniformLocation, floatLocation[0], floatLocation[1], floatLocation[2]);
				break;
			}	

			case TYPE_BOOLEAN:
			{
				glUniform1i(uniformLocation, m_boolData);
				break;
			}

			case TYPE_INTEGER:
			{
				glUniform1i(uniformLocation, m_intData);
				break;
			}	

			case TYPE_UNSIGNED_INTEGER:
			{
				glUniform1ui(uniformLocation, m_uintData);
				break;
			}
			
			default:
				return false;
			}

			return true;
		}

		bool OpenGLUniform::_checkDataInited()
		{
			if (m_dUniformArray || m_fUniformArray)
			{
				return true;
			}

			return false;
		}
	}
}