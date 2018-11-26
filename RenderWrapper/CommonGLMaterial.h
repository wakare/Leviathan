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
		CommonGLMaterial(GLColor ambient = {0.0f, 0.0f, 0.0f}, GLColor diffuse = { 0.0f, 0.0f, 0.0f }, GLColor specular = { 0.0f, 0.0f, 0.0f }, float fShininess = 32.0f);
		~CommonGLMaterial() {}
		
		bool ApplyMaterial(GLuint program);

	private:
		GLColor m_CAmbient;
		GLColor m_CDiffuse;
		GLColor m_CSpecular;
		float m_fShininess;
	};
}