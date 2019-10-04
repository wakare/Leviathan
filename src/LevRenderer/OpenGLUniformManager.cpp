#include "OpenGLUniformManager.h"
#include "OpenGLProgramUniformManager.h"
#include "OpenGLShaderProgram.h"

namespace Leviathan
{
	namespace Renderer
	{
		OpenGLUniformManager::OpenGLUniformManager()
		{
		}

		bool OpenGLUniformManager::CreateProgramUniformManager(LSPtr<OpenGLShaderProgram> shader_program,
			LSPtr<OpenGLProgramUniformManager>& out)
		{
			out.Reset(new OpenGLProgramUniformManager(*this, shader_program->GetShaderProgram()));
			return true;
		}
	}
}
