#pragma once
#include <GL/glew.h>

namespace Leviathan
{
	class GLMaterial
	{
	public:
		GLMaterial() {};
		virtual bool ApplyMaterial(GLuint program) = 0;
	};
}