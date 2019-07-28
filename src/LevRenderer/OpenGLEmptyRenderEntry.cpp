#include "OpenGLEmptyRenderEntry.h"

namespace Leviathan
{
	namespace RenderService
	{

	}

	Renderer::OpenGLEmptyRenderEntry::OpenGLEmptyRenderEntry(unsigned id)
		: OpenGLRenderEntry(id)
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