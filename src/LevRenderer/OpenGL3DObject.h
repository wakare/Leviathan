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
			OpenGL3DObject(GLuint primType, GLfloat* pVertexArrayData, GLuint vertexSize, GLint vertexMask, LPtr<Eigen::Matrix4f> pModelMatrix = nullptr, LPtr<OpenGLMaterial> pCommonGLMaterial = nullptr, unsigned* pIndexArrayData = nullptr, unsigned uIndexArrayCount = 0U);

			bool Init();
			bool Render(GLuint shaderProgram);
			bool ApplyMaterial(GLuint shaderProgram);
			bool ApplyModelMatrix(LPtr<OpenGLUniform>& modelUniform);
			bool ApplyWorldMatrix(LPtr<OpenGLUniform>& worldUniform);
			bool ApplyUniform(GLuint shaderProgram);

		private:
			bool _updateDefaultUseVertexColorUniform(GLuint shaderProgram);
			bool _updateVertexMaskUniform(GLuint shaderProgram);

			GLfloat* m_pData;
			GLuint* m_pIndexData;
			GLuint m_uIndexArrayCount;
			GLboolean m_bUseIndexArray;
		};
	}
}
