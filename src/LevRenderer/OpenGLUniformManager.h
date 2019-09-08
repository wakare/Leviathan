#pragma once

#include "LSPtr.h"
#include "gl/glew.h"

namespace Leviathan
{
	namespace Renderer
	{
		class IOpenGLUniform;

		class OpenGLUniformManager
		{
		public:
			OpenGLUniformManager(GLuint shader_program);

			void ApplyUniform(LSPtr<IOpenGLUniform> uniform);

		private:
			GLuint m_shader_program;
		};
	}
}

