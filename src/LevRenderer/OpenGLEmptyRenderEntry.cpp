#include "OpenGLEmptyRenderEntry.h"

namespace Leviathan
{
	Renderer::OpenGLEmptyRenderEntry::OpenGLEmptyRenderEntry(OpenGLRenderEntryManager& manager, unsigned id)
		: OpenGLRenderEntry(manager, id)
	{

	}

	bool Renderer::OpenGLEmptyRenderEntry::_init()
	{
		return true;
	}

	bool Renderer::OpenGLEmptyRenderEntry::Render(GLuint shaderProgram)
	{
		return true;
	}

}