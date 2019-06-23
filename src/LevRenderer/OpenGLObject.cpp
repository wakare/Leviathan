#include "OpenGLObject.h"
#include "OpenGLUniform.h"
#include "OpenGLMaterial.h"

namespace Leviathan
{
	namespace Renderer
	{
		OpenGLObject::OpenGLObject(unsigned id, GLuint primType, GLuint vertexCount, GLint vertexMask, LPtr<OpenGLMaterial> pMaterial /*= nullptr*/) 
			: m_ID(id)
			, m_VAO(0)
			, m_VBO(0)
			, m_IBO(0)
			, m_primitiveType(primType)
			, m_vertexCount(vertexCount)
			, m_vertexAttributeMask(vertexMask)
			, m_pMaterial(pMaterial)
			, m_shader_program(nullptr)
		{
			SetVisible(true);
		}

		OpenGLObject::~OpenGLObject() 
		{
		};

		unsigned OpenGLObject::GetID() const
		{
			return m_ID;
		}

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

		void OpenGLObject::SetVisible(bool visible)
		{
			m_visible = visible;
		}

		bool OpenGLObject::GetVisible() const
		{
			return m_visible;
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

		void OpenGLObject::SetShaderProgram(LPtr<OpenGLShaderProgram> shader_program)
		{
			m_shader_program = shader_program;
		}

		const Leviathan::LPtr<Leviathan::Renderer::OpenGLShaderProgram> OpenGLObject::GetShaderProgram() const
		{
			return m_shader_program;
		}

		void OpenGLObject::AddPreProcess(std::function<void()> fn)
		{
			m_preprocess_fns.push_back(fn);
		}

		void OpenGLObject::AddPostProcess(std::function<void()> fn)
		{
			m_postprocess_fns.push_back(fn);
		}

		bool OpenGLObject::PreProcess()
		{
			for (auto& fn : m_preprocess_fns)
			{
				fn();
			}

			return true;
		}

		bool OpenGLObject::PostProcess()
		{
			for (auto& fn : m_postprocess_fns)
			{
				fn();
			}

			return true;
		}

	}
}
