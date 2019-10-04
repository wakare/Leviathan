#pragma once

#include "LSPtr.h"
#include "gl/glew.h"

namespace Leviathan
{
	namespace Renderer
	{
		class IOpenGLUniform;
		class OpenGLUniformManager;

		class OpenGLProgramUniformManager
		{
		public:
			OpenGLProgramUniformManager(OpenGLUniformManager& uniform_manager, GLuint shader_program);
			void ApplyUniform(LSPtr<IOpenGLUniform> uniform);

		private:
			OpenGLUniformManager& m_uniform_manager;
			GLuint m_shader_program;
		};
	}
}

