#pragma once

#include "OpenGLObject.h"

namespace Leviathan
{
	namespace Renderer
	{
		static unsigned INVALID_ID = UINT_MAX;

		class OpenGLEmptyObject : public OpenGLObject
		{
		public:
			OpenGLEmptyObject(unsigned id = INVALID_ID);

		protected:
			virtual bool _init();
			virtual bool Render(GLuint shaderProgram);
		};
	}
}