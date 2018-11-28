#pragma once
#define GLEW_STATIC
#include <GL\glew.h>
#include <LPtr.h>
#include "IGLMaterial.h"
#include "GLUniform.h"
#include "GLCamera.h"

namespace Leviathan
{
	class GLObject
	{
	public:
		enum VertexAttributeType
		{
			VERTEX_ATTRIBUTE_XYZ = 0x1,		// Coord XYZ
			VERTEX_ATTRIBUTE_RGBA = 0x2,	// Color RGBAs
			VERTEX_ATTRIBUTE_NXYZ = 0x4,	// Normal XYZ
		};

		GLObject(GLuint primType, GLuint vertexCount, GLint vertexMask, LPtr<Matrix4f> pModelMatrix = nullptr, LPtr<IGLMaterial> pCommonGLMaterial = nullptr ) :
			m_bLightEnable(true),
			m_VAO(0), 
			m_VBO(0), 
			m_primitiveType(primType), 
			m_vertexCount(vertexCount), 
			m_vertexAttributeMask(vertexMask),
			m_pCommonGLMaterial(pCommonGLMaterial),
			m_pModelMatrix(pModelMatrix)
		{
		}

		GLuint GetVAO() { return m_VAO; }
		GLuint GetVBO() { return m_VBO; }
		GLuint GetPrimType() { return m_primitiveType; }
		GLuint GetVertexCount() { return m_vertexCount; }
		GLuint GetVertexMask() { return m_vertexAttributeMask; }
		GLboolean GetLightEnable() { return m_bLightEnable; }

		void SetModelMatrix(const Matrix4f& refModelMatrix) { if (!m_pModelMatrix) { m_pModelMatrix = new Matrix4f(); } m_pModelMatrix->SetData(refModelMatrix.GetData()); }
		void SetMaterial(LPtr<IGLMaterial> pMaterial) { m_pCommonGLMaterial = pMaterial; }
		void SetLightEnable(bool bLightEnable) { m_bLightEnable = bLightEnable; }

		virtual ~GLObject() {};
		virtual bool Init() = 0;
		virtual bool ApplyMaterial(GLuint shaderProgram) = 0;
		virtual bool ApplyModelMatrix(Leviathan::LPtr<Leviathan::GLUniform>& modelUniform) = 0;
		virtual bool Render(GLuint shaderProgram) = 0;

	protected:
		GLboolean m_bLightEnable;
		GLuint m_VAO;
		GLuint m_VBO;
		GLuint m_primitiveType;
		GLuint m_vertexCount;
		GLint m_vertexAttributeMask;
		LPtr<IGLMaterial> m_pCommonGLMaterial;
		LPtr<Matrix4f> m_pModelMatrix;
	};
}