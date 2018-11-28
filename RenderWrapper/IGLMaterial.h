#pragma once
#include <GL/glew.h>

namespace Leviathan
{
	class IGLMaterial
	{
	public:
		IGLMaterial() {};

		virtual ~IGLMaterial() {}
		virtual bool ApplyMaterial(GLuint program) = 0;
	};
}