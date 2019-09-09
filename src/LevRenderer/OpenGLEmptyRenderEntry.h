#pragma once

#include "OpenGLRenderEntry.h"

namespace Leviathan
{
	namespace Renderer
	{
		class OpenGLRenderEntryManager;

		class OpenGLEmptyRenderEntry : public OpenGLRenderEntry
		{
		public:
			OpenGLEmptyRenderEntry(OpenGLRenderEntryManager& manager, unsigned id);

		protected:
			bool _init() override;
			bool Render(GLuint shaderProgram) override;
		};
	}
}