#pragma once

#include "OpenGLRenderEntry.h"

namespace Leviathan
{
	namespace Renderer
	{
		static unsigned INVALID_ID = UINT_MAX;

		class OpenGLEmptyRenderEntry : public OpenGLRenderEntry
		{
		public:
			OpenGLEmptyRenderEntry(unsigned id = INVALID_ID);

		protected:
			virtual bool _init();
			virtual bool Render(GLuint shaderProgram);
		};
	}
}