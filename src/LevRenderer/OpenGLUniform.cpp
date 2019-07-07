#include "OpenGLUniform.h"

namespace Leviathan
{
	namespace Renderer
	{
		using namespace Scene;

		OpenGLUniform::OpenGLUniform(const Scene::LevRAttrUniform& scene_uniform)
			: m_scene_uniform(scene_uniform)
		{

		}

		const std::string& OpenGLUniform::GetUniformName() const
		{
			return m_scene_uniform.GetName();
		}

		bool OpenGLUniform::Apply(GLuint program)
		{
			GLint uniformLocation = glGetUniformLocation(program, GetUniformName().c_str());
			if (uniformLocation == -1)
			{
				throw "OpenGLUniform::Apply(GLuint program) --> Get uniform location failed.";
				return false;
			}

			const void* uniform_data = m_scene_uniform.GetData().GetArrayData();

			switch (m_scene_uniform.GetUniformType())
			{
			case TYPE_FLOAT_MAT4:
			{
				glUniformMatrix4fv(uniformLocation, 1, false, static_cast<const GLfloat*>(uniform_data));
				break;
			}	

			case TYPE_FLOAT_VEC3:
			{
				const float* floatLocation = static_cast<const float*>(uniform_data);
				glUniform3f(uniformLocation, floatLocation[0], floatLocation[1], floatLocation[2]);
				break;
			}	

			case TYPE_BOOLEAN:
			{
				const bool* bool_data = static_cast<const bool*>(uniform_data);
				glUniform1i(uniformLocation, *bool_data);
				break;
			}

			case TYPE_INTEGER:
			{
				const int* int_data = static_cast<const int*>(uniform_data);
				glUniform1i(uniformLocation, *int_data);
				break;
			}	

			case TYPE_UNSIGNED_INTEGER:
			{
				const unsigned* uint_data = static_cast<const unsigned*>(uniform_data);
				glUniform1ui(uniformLocation, *uint_data);
				break;
			}
			
			default:
				return false;
			}

			return true;
		}
	}
}