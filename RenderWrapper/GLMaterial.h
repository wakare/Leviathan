#pragma once
#include <GL/glew.h>

namespace Leviathan
{
	class GLMaterial
	{
	public:
		GLMaterial() {};
		virtual bool SetMaterial(GLuint shaderProgram) = 0;
	};
}