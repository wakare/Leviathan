#pragma once
#include "GLMaterial.h"
#include "GLColor.h"

#define GLEW_STATIC
#include <GL\glew.h>

namespace Leviathan
{
	class CommonGLMaterial : public GLMaterial
	{
	public:
		CommonGLMaterial();
		bool SetMaterial(GLuint program);

	private:
		GLColor m_CAmbient;
		GLColor m_CDiffuse;
		GLColor m_CSpecular;
		float m_fShininess;
	};
}