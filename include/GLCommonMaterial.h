#pragma once
#include "IGLMaterial.h"
#include "GLColor.h"
#include "GLTexture.h"
#include "LPtr.h"
#include <GL\glew.h>
#include <vector>

namespace Leviathan
{
	class GLCommonMaterial : public IGLMaterial
	{
	public:
		GLCommonMaterial(GLColor ambient = {0.0f, 0.0f, 0.0f}, GLColor diffuse = { 0.0f, 0.0f, 0.0f }, GLColor specular = { 0.0f, 0.0f, 0.0f }, float fShininess = 32.0f);
		~GLCommonMaterial() {}
		
		bool ApplyMaterial(GLuint program);
		bool UnApplyMaterial(GLuint program);
		bool AddTexture2D(LPtr<GLTexture2D> pTexture2D);

	private:
		GLColor m_CAmbient;
		GLColor m_CDiffuse;
		GLColor m_CSpecular;
		GLfloat m_fShininess;
		GLuint m_uMaxTexture2DCount;

		std::vector<LPtr<GLTexture2D>> m_pTexture2DVec;
	};
}