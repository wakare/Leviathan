#pragma once

#include "OpenGLObject.h"

namespace Leviathan
{
	namespace Renderer
	{
		class OpenGLEmptyObject : public OpenGLObject
		{
		public:
			OpenGLEmptyObject(unsigned id);

			bool Init();
			bool Update();
			bool Render(GLuint shaderProgram);
		};
	}
}