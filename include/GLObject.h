#pragma once

#include <map>
#include <GL\glew.h>
#include <LPtr.h>
#include "IGLMaterial.h"
#include "GLUniform.h"
#include "Camera.h"

namespace Leviathan
{
	class GLObject
	{
	public:
		enum VertexAttributeType
		{
			VERTEX_ATTRIBUTE_XYZ  = 0x1,	// Coord XYZ
			VERTEX_ATTRIBUTE_RGBA = 0x2,	// Color RGBAs
			VERTEX_ATTRIBUTE_NXYZ = 0x4,	// Normal XYZ
			VERTEX_ATTRIBUTE_TEX  = 0x8,
		};

		GLObject(GLuint primType, GLuint vertexCount, GLint vertexMask, LPtr<Eigen::Matrix4f> pModelMatrix = nullptr, LPtr<IGLMaterial> pCommonGLMaterial = nullptr) :
			m_bLightEnable(true),
			m_bUseDefaultVertexColor(false),
			m_VAO(0), 
			m_VBO(0), 
			m_IBO(0),
			m_primitiveType(primType), 
			m_vertexCount(vertexCount), 
			m_vertexAttributeMask(vertexMask),
			m_pCommonGLMaterial(pCommonGLMaterial),
			m_pModelMatrix(pModelMatrix)
		{
		}

		virtual ~GLObject() {};

		GLuint GetVAO() { return m_VAO; }
		GLuint GetVBO() { return m_VBO; }
		GLuint GetIBO() { return m_IBO; }
		GLuint GetPrimType() { return m_primitiveType; }
		GLuint GetVertexCount() { return m_vertexCount; }
		GLuint GetVertexMask() { return m_vertexAttributeMask; }
		GLboolean GetLightEnable() { return m_bLightEnable; }

		void SetModelMatrix(const Eigen::Matrix4f& refModelMatrix) { 
			if (!m_pModelMatrix)  m_pModelMatrix = new Eigen::Matrix4f(refModelMatrix); 
			*m_pModelMatrix = refModelMatrix; 
		}

		void SetMaterial(LPtr<IGLMaterial> pMaterial) { m_pCommonGLMaterial = pMaterial; }
		void SetLightEnable(bool bLightEnable) { m_bLightEnable = bLightEnable; }
		void SetDefaultVertexColorEnable(bool bUseDefaultVertexColor) { m_bUseDefaultVertexColor = bUseDefaultVertexColor; }
		GLboolean HasMaterial() const { return m_pCommonGLMaterial != nullptr; }

		void AddUniform(LPtr<GLUniform> pUniform) { m_pUniforms[pUniform->GetUniformName()] = pUniform; }
		
		virtual bool Init() = 0;
		virtual bool ApplyMaterial(GLuint shaderProgram) = 0;
		virtual bool ApplyModelMatrix(LPtr<GLUniform>& modelUniform) = 0;
		virtual bool ApplyUniform(GLuint shaderProgram) = 0;
		virtual bool Render(GLuint shaderProgram) = 0;

	protected:
		GLboolean m_bLightEnable;
		GLboolean m_bUseDefaultVertexColor;

		GLuint m_VAO;
		GLuint m_VBO;
		GLuint m_IBO;
		GLuint m_primitiveType;
		GLuint m_vertexCount;
		GLint m_vertexAttributeMask;
		LPtr<IGLMaterial> m_pCommonGLMaterial;
		LPtr<Eigen::Matrix4f> m_pModelMatrix;
		std::map<std::string, LPtr<GLUniform>> m_pUniforms;
	};
}