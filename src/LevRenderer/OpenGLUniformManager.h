#pragma once
#include <vector>
#include "LSPtr.h"

namespace Leviathan
{
	namespace Renderer
	{
		class OpenGLProgramUniformManager;
		class OpenGLShaderProgram;

		class OpenGLUniformManager
		{
		public:
			OpenGLUniformManager();

			bool CreateProgramUniformManager(LSPtr<OpenGLShaderProgram> shader_program, LSPtr<OpenGLProgramUniformManager>& out);

		private:
			std::vector<LSPtr<OpenGLProgramUniformManager>> m_program_uniforms;
		};
	}
}
