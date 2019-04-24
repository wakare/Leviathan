#include "OpenGLEmptyObject.h"

namespace Leviathan
{
	namespace RenderService
	{

	}

	Renderer::OpenGLEmptyObject::OpenGLEmptyObject()
		: OpenGLObject(0, 0, 0)
	{

	}

	bool Renderer::OpenGLEmptyObject::Init()
	{
		return true;
	}

	bool Renderer::OpenGLEmptyObject::Update()
	{
		return true;
	}

	bool Renderer::OpenGLEmptyObject::Render(GLuint shaderProgram)
	{
		EXIT_IF_FALSE(ApplyUniform(shaderProgram));

		return true;
	}

}