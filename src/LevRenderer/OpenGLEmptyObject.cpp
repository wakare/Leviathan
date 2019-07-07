#include "OpenGLEmptyObject.h"

namespace Leviathan
{
	namespace RenderService
	{

	}

	Renderer::OpenGLEmptyObject::OpenGLEmptyObject(unsigned id)
		: OpenGLObject(id)
	{

	}

	bool Renderer::OpenGLEmptyObject::_init()
	{
		return true;
	}

	bool Renderer::OpenGLEmptyObject::Render(GLuint shaderProgram)
	{
		EXIT_IF_FALSE(ApplyUniform(shaderProgram));

		return true;
	}

}