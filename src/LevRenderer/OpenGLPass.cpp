#include "OpenGLPass.h"
#include "OpenGLLight.h"
#include "OpenGLUniform.h"
#include "OpenGLObject.h"

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
			m_GLObjectMap[pObject->GetID()].push_back(pObject);
		}

		void OpenGLPass::AddGLObject(unsigned id, const std::vector<LPtr<OpenGLObject>>& pGLObjectVec)
		{
			m_GLObjectMap[id].insert(m_GLObjectMap[id].end(), pGLObjectVec.begin(), pGLObjectVec.end());
		}

		bool OpenGLPass::ReplaceGLObject(unsigned id, const std::vector<LPtr<OpenGLObject>>& objects)
		{
			auto itFind = m_GLObjectMap.find(id);
			if (itFind == m_GLObjectMap.end())
			{
				return false;
			}

			itFind->second = objects;
			return true;
		}

		void OpenGLPass::RemoveGLObject(unsigned id)
		{
			auto itFind = m_GLObjectMap.find(id);
			if (itFind != m_GLObjectMap.end())
			{
				m_GLObjectMap.erase(itFind);
			}
		}

		void OpenGLPass::ClearGLObject()
		{
			m_GLObjectMap.clear();
		}

		void OpenGLPass::AddGLLight(LPtr<OpenGLLight> pLight) 
		{ 
			m_lights.push_back(pLight); 
		}

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

		GLboolean OpenGLPass::GetLightEnable() const
		{
			return m_bLightEnable;
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

		bool OpenGLPass::_findGLObject(unsigned id, std::vector<LPtr<OpenGLObject>>& out)
		{
			auto itFind = m_GLObjectMap.find(id);
			if (itFind == m_GLObjectMap.end())
			{
				return false;
			}

			out = itFind->second;
			return true;
		}
	}
}