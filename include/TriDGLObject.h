#pragma once

#include "GLObject.h"
#include "LPtr.h"
#include "GLCommonMaterial.h"

namespace Leviathan
{
	class TriDGLObject : public GLObject
	{
	public:
		TriDGLObject(GLuint primType, GLfloat* pVertexArrayData, GLuint vertexSize, GLint vertexMask, LPtr<Eigen::Matrix4f> pModelMatrix = nullptr, LPtr<GLCommonMaterial> pCommonGLMaterial = nullptr, unsigned* pIndexArrayData = nullptr, unsigned uIndexArrayCount = 0U) :
			GLObject(primType, vertexSize, vertexMask, pModelMatrix, TryCast<GLCommonMaterial, IGLMaterial>(pCommonGLMaterial)),
			m_pData(pVertexArrayData),
			m_pIndexData(pIndexArrayData),
			m_uIndexArrayCount(uIndexArrayCount)
		{
			Init();
		};

		bool Init();
		bool Render(GLuint shaderProgram);
		bool ApplyMaterial(GLuint shaderProgram);
		bool ApplyModelMatrix(Leviathan::LPtr<Leviathan::GLUniform>& modelUniform);
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