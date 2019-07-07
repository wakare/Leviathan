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

		protected:
			virtual bool _init();
			virtual bool Render(GLuint shaderProgram);
		};
	}
}