#include "OpenGLObject.h"
#include "OpenGLUniform.h"
#include "OpenGLMaterial.h"

namespace Leviathan
{
	namespace Renderer
	{
		OpenGLObject::OpenGLObject(GLuint primType, GLuint vertexCount, GLint vertexMask, LPtr<Eigen::Matrix4f> pModelMatrix /*= nullptr*/, LPtr<OpenGLMaterial> pCommonGLMaterial /*= nullptr*/) :
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

		OpenGLObject::~OpenGLObject() 
		{
		};

		GLuint OpenGLObject::GetVAO()
		{
			return m_VAO;
		}

		GLuint OpenGLObject::GetVBO()
		{
			return m_VBO;
		}

		GLuint OpenGLObject::GetIBO()
		{
			return m_IBO;
		}

		GLuint OpenGLObject::GetPrimType()
		{
			return m_primitiveType;
		}

		GLuint OpenGLObject::GetVertexCount()
		{
			return m_vertexCount;
		}

		GLuint OpenGLObject::GetVertexMask()
		{
			return m_vertexAttributeMask;
		}

		GLboolean OpenGLObject::GetLightEnable()
		{
			return m_bLightEnable;
		}

		void OpenGLObject::SetModelMatrix(const Eigen::Matrix4f& refModelMatrix) 
		{
			m_pModelMatrix.Reset(new Eigen::Matrix4f(refModelMatrix));
		}

		void OpenGLObject::SetWorldMatrix(const Eigen::Matrix4f & refWorldMatrix)
		{
			m_pWorldMatrix.Reset(new Eigen::Matrix4f(refWorldMatrix));
		}

		void OpenGLObject::SetMaterial(LPtr<OpenGLMaterial> pMaterial) 
		{
			m_pCommonGLMaterial = pMaterial; 
		}

		void OpenGLObject::SetLightEnable(bool bLightEnable) 
		{
			m_bLightEnable = bLightEnable; 
		}

		void OpenGLObject::SetDefaultVertexColorEnable(bool bUseDefaultVertexColor) 
		{
			m_bUseDefaultVertexColor = bUseDefaultVertexColor; 
		}

		GLboolean OpenGLObject::HasMaterial() const 
		{
			return m_pCommonGLMaterial != nullptr; 
		}

		void OpenGLObject::AddUniform(LPtr<OpenGLUniform> pUniform) 
		{ 
			m_pUniforms[pUniform->GetUniformName()] = pUniform; 
		}
	}
}
