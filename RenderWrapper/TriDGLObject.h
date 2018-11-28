#pragma once
#include "GLObject.h"
#include "LPtr.h"
#include "GLCommonMaterial.h"

namespace Leviathan
{
	class TriDGLObject : public GLObject
	{
	public:
		TriDGLObject(GLuint primType, GLfloat* data, GLuint vertexSize, GLint vertexMask, LPtr<Matrix4f> pModelMatrix = nullptr, LPtr<GLCommonMaterial> pCommonGLMaterial = nullptr) :
			GLObject(primType, vertexSize, vertexMask, pModelMatrix, TryCast<GLCommonMaterial, IGLMaterial>(pCommonGLMaterial)),
			m_data(data)
		{
			Init();
		};

		bool Init();
		bool Render(GLuint shaderProgram);
		bool ApplyMaterial(GLuint fragmentProgram);
		bool UnApplyMaterial(GLuint shaderProgram);
		bool ApplyModelMatrix(Leviathan::LPtr<Leviathan::GLUniform>& modelUniform);

	private:
		GLfloat* m_data;
	};
}