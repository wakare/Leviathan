#pragma once

#include <gl/glew.h>
#include <Eigen/Dense>
#include "OpenGLObject.h"
#include "LPtr.h"

namespace Leviathan
{
	namespace Renderer
	{
		class OpenGLUniform;

		class OpenGL3DObject : public OpenGLObject
		{
		public:
			OpenGL3DObject(GLuint primType, GLfloat* pVertexArrayData, GLuint vertexSize, GLint vertexMask, LPtr<OpenGLMaterial> pCommonGLMaterial = nullptr, unsigned* pIndexArrayData = nullptr, unsigned uIndexArrayCount = 0U);

			bool SetLightEnable(bool enable);
			bool SetVertexMask(unsigned mask);
			bool SetUseDefaultColor(bool use);

			bool Init();
			bool Update();
			bool Render(GLuint shaderProgram);

		private:
			GLfloat* m_pData;
			GLuint* m_pIndexData;
			GLuint m_uIndexArrayCount;

			LPtr<OpenGLUniform> m_pLightEnableUniform;
			LPtr<OpenGLUniform> m_pVertexMaskUniform;
			LPtr<OpenGLUniform> m_pUseDefaultColorUniform;
			GLboolean m_bUseIndexArray;
		};
	}
}
