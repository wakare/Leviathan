#pragma once
#include "GLObject.h"
#include "LPtr.h"
#include "CommonGLMaterial.h"

namespace Leviathan
{
	class TriDGLObject : public GLObject
	{
	public:
		TriDGLObject(GLuint primType, GLfloat* data, GLuint vertexSize, GLint vertexMask, LPtr<Matrix4f> pModelMatrix = nullptr, LPtr<CommonGLMaterial> pCommonGLMaterial = nullptr) :
			GLObject(primType, vertexSize, vertexMask, pModelMatrix, TryCast<CommonGLMaterial, GLMaterial>(pCommonGLMaterial)),
			m_data(data)
		{
			Init();
		};

		bool Init();
		bool Render(GLuint shaderProgram);
		bool SetMaterial(GLuint fragmentProgram);
		bool SetModelMatrix(Leviathan::LPtr<Leviathan::GLUniform>& modelUniform);

	private:
		GLfloat* m_data;
	};
}