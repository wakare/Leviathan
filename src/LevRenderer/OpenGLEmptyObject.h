#pragma once

#include "OpenGLObject2.h"

namespace Leviathan
{
	namespace Renderer
	{
		class OpenGLEmptyObject : public OpenGLObject2
		{
		public:
			OpenGLEmptyObject(unsigned id);

		protected:
			virtual bool _init();
			virtual bool Render(GLuint shaderProgram);
		};
	}
}