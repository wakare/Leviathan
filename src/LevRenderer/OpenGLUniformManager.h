#pragma once

#include "LPtr.h"
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

			void ApplyUniform(LPtr<IOpenGLUniform> uniform);

		private:
			GLuint m_shader_program;
		};
	}
}

