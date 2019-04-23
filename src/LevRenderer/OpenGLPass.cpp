#include "OpenGLPass.h"
#include "OpenGLLight.h"
#include "OpenGLUniform.h"

namespace Leviathan
{
	namespace Renderer
	{
		OpenGLPass::OpenGLPass(LPtr<OpenGLShaderProgram> shaderProgram) :
			m_pGLShaderProgram(shaderProgram),
			m_nPolygonMode(GL_FILL),
			m_bLightEnable(true),
			m_bDepthTestEnable(true)
		{

		};

		void OpenGLPass::AddGLObject(LPtr<OpenGLObject> pObject)
		{
			if (_findGLObject(pObject) == m_GLObjects.end())
			{
				m_GLObjects.push_back(pObject);			
			}
		}

		void OpenGLPass::AddGLObject(std::vector<LPtr<OpenGLObject>>& pGLObjectVec)
		{
			for (auto& pGLObject : pGLObjectVec)
			{
				AddGLObject(pGLObject);
			}
		}

		void OpenGLPass::RemoveGLObject(LPtr<OpenGLObject> pObject)
		{
			auto it = _findGLObject(pObject);
			if (it != m_GLObjects.end())
			{
				m_GLObjects.erase(it);
			}
		}

		void OpenGLPass::ClearGLObject()
		{
			m_GLObjects.clear();
		}

		void OpenGLPass::AddGLLight(LPtr<OpenGLLight> pLight) 
		{ 
			m_lights.push_back(pLight); 
		}

		const std::vector<Leviathan::LPtr<Leviathan::Renderer::OpenGLObject>> OpenGLPass::GetGLObjects()
		{
			return m_GLObjects; 
		};

		OpenGLPass::~OpenGLPass()
		{

		}

		void OpenGLPass::AddPreProcess(Process process) 
		{ 
			m_PreRenderCallBacks.push_back(process); 
		};

		void OpenGLPass::AddPostProcess(Process process)
		{
			m_PostRenderCallBacks.push_back(process); 
		};

		void OpenGLPass::SetPolygonMode(GLuint nPolygonMode)
		{ 
			m_nPolygonMode = nPolygonMode; 
		}

		void OpenGLPass::SetLightEnable(GLboolean bOpen) 
		{
			m_bLightEnable = bOpen; 
		}

		void OpenGLPass::SetDepthTestEnable(GLboolean bDepthTestEnable) 
		{ 
			m_bDepthTestEnable = bDepthTestEnable; 
		}

		void OpenGLPass::AddUniform(LPtr<OpenGLUniform> pUniform)
		{
			m_pUniforms.push_back(pUniform);
		}

		void OpenGLPass::RemoveUniform(LPtr<OpenGLUniform> pUniform)
		{
			auto itFind = std::find(m_pUniforms.begin(), m_pUniforms.end(), pUniform);
			if (itFind != m_pUniforms.end())
			{
				m_pUniforms.erase(itFind);
			}
		}

		void OpenGLPass::_applyUniforms()
		{
			for (auto& pUniform : m_pUniforms)
			{
				pUniform->Apply(m_pGLShaderProgram);
			}
		}

		std::vector<LPtr<OpenGLObject>>::iterator OpenGLPass::_findGLObject(LPtr<OpenGLObject>& pObject)
		{
			return std::find(m_GLObjects.begin(), m_GLObjects.end(), pObject);
		}

	}
}