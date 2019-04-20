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
			m_pMaterial(pCommonGLMaterial),
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
			m_pMaterial = pMaterial; 
		}

		bool OpenGLObject::ApplyMaterial(GLuint shaderProgram)
		{
			if (!m_pMaterial) return false;
			return m_pMaterial->ApplyMaterial(shaderProgram);
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
			return m_pMaterial != nullptr; 
		}

		void OpenGLObject::AddUniform(LPtr<OpenGLUniform> pUniform) 
		{ 
			m_pUniforms.push_back(pUniform);
		}

		void OpenGLObject::RemoveUniform(LPtr<OpenGLUniform> pUniform)
		{
			auto itFind = std::find(m_pUniforms.begin(), m_pUniforms.end(), pUniform);
			if (itFind != m_pUniforms.end())
			{
				m_pUniforms.erase(itFind);
			}
		}

		bool OpenGLObject::ApplyUniform(GLuint shaderProgram)
		{
			for (auto& pUniform : m_pUniforms)
			{
				EXIT_IF_FALSE(pUniform->Apply(shaderProgram));
			}

			return true;
		}

	}
}
