#pragma once

#include <GL\glew.h>
#include <vector>
#include "IGLMaterial.h"
#include "Color.h"
#include "GLTexture.h"
#include "LPtr.h"

namespace Leviathan
{
	class GLCommonMaterial : public IGLMaterial
	{
	public:
		GLCommonMaterial(Color ambient = {0.0f, 0.0f, 0.0f}, Color diffuse = { 0.0f, 0.0f, 0.0f }, Color specular = { 0.0f, 0.0f, 0.0f }, float fShininess = 32.0f);
		~GLCommonMaterial() {}
		
		bool ApplyMaterial(GLuint program);
		bool UnApplyMaterial(GLuint program);
		bool AddTexture2D(LPtr<GLTexture2D> pTexture2D);

	private:
		Color m_CAmbient;
		Color m_CDiffuse;
		Color m_CSpecular;
		GLfloat m_fShininess;
		GLuint m_uMaxTexture2DCount;

		std::vector<LPtr<GLTexture2D>> m_pTexture2DVec;
	};
}