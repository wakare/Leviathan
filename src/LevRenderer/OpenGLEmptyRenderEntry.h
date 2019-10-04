#pragma once

#include "OpenGLRenderEntry.h"

namespace Leviathan
{
	namespace Renderer
	{
		class OpenGLRenderResourceManager;

		class OpenGLEmptyRenderEntry : public OpenGLRenderEntry
		{
		public:
			OpenGLEmptyRenderEntry(OpenGLRenderResourceManager& manager, unsigned id);

		protected:
			bool _init() override;
			bool Render(GLuint shaderProgram) override;
		};
	}
}