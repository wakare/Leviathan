#include "OpenGLUniformManager.h"
#include "IOpenGLUniform.h"

namespace Leviathan
{
	namespace Renderer
	{
		OpenGLUniformManager::OpenGLUniformManager(GLuint shader_program)
			: m_shader_program(shader_program)
		{
			
		}

		void OpenGLUniformManager::ApplyUniform(LSPtr<IOpenGLUniform> uniform)
		{
			uniform->Apply(m_shader_program);
		}
	}
}