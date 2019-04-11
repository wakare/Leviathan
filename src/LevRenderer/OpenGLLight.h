#pragma once

#include <gl/glew.h>

namespace Leviathan
{
	namespace Renderer
	{
		class OpenGLLight
		{
		public:
			virtual bool SetLightUniformVar(GLuint shaderProgram) = 0;
		};
	}
}