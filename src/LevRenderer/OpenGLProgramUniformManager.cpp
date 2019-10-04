#include "OpenGLProgramUniformManager.h"
#include "IOpenGLUniform.h"

namespace Leviathan
{
	namespace Renderer
	{
		OpenGLProgramUniformManager::OpenGLProgramUniformManager(OpenGLUniformManager& uniform_manager,
			GLuint shader_program)
			: m_uniform_manager(uniform_manager)
			, m_shader_program(shader_program)
		{
		}

		void OpenGLProgramUniformManager::ApplyUniform(LSPtr<IOpenGLUniform> uniform)
		{
			uniform->Apply(m_shader_program);
		}
	}
}