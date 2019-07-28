#pragma once

#include <gl/glew.h>
#include <vector>
#include "Color.h"
#include "LPtr.h"

namespace Leviathan
{
	namespace Renderer
	{
		class OpenGLTextureUniform;

		class OpenGLMaterial
		{
		public:
			OpenGLMaterial(Color ambient = { 0.0f, 0.0f, 0.0f }, Color diffuse = { 0.0f, 0.0f, 0.0f }, Color specular = { 0.0f, 0.0f, 0.0f }, float fShininess = 32.0f);
			~OpenGLMaterial() {}

			bool ApplyMaterial(GLuint program);
			bool UnApplyMaterial(GLuint program);
			bool AddTexture2D(LPtr<OpenGLTextureUniform> pTexture2D);

		private:
			Color m_CAmbient;
			Color m_CDiffuse;
			Color m_CSpecular;
			GLfloat m_fShininess;
			GLuint m_uMaxTexture2DCount;

			std::vector<LPtr<OpenGLTextureUniform>> m_pTexture2DVec;
		};
	}
}
