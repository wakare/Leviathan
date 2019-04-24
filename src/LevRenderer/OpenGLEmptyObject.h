#pragma once

#include "OpenGLObject.h"

namespace Leviathan
{
	namespace Renderer
	{
		class OpenGLEmptyObject : public OpenGLObject
		{
		public:
			OpenGLEmptyObject();

			bool Init();
			bool Update();
			bool Render(GLuint shaderProgram);
		};
	}
}