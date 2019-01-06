#pragma once

#include <memory>
#include <vector>
#include <functional>
#include "GLObject.h"
#include "GLShaderProgram.h"
#include "LPtr.h"
#include "GLLight.h"

namespace Leviathan
{
	class GLPass
	{
		typedef std::function<void(void)> Process;
	public:
		GLPass(LPtr<GLShaderProgram> shaderProgram) :
			m_pGLShaderProgram(shaderProgram), 
			m_nPolygonMode(GL_FILL), 
			m_bLightEnable(true),
			m_bDepthTestEnable(true)
		{

		};

		void AddGLObject(LPtr<GLObject> pObject) 
		{ 
			if (_findGLObject(pObject) == m_GLObjects.end())
			{
				m_GLObjects.push_back(pObject);
			}
		}

		void AddGLObject(std::vector<LPtr<GLObject>>& pGLObjectVec)
		{
			for (auto& pGLObject : pGLObjectVec)
			{
				AddGLObject(pGLObject);
			}
		}

		void DelGLObject(LPtr<GLObject> pObject) 
		{
			auto it = _findGLObject(pObject);
			if (it != m_GLObjects.end())
			{
				m_GLObjects.erase(it);
			}
		}

		void AddGLLight(LPtr<GLLight> pLight) { m_lights.push_back(pLight); }
		const std::vector<LPtr<GLObject>> GetGLObjects() { return m_GLObjects; };
		
		virtual ~GLPass() {};
		virtual bool Init() = 0;
		virtual void Render() = 0;

		void AddPreProcess(Process process) { m_PreRenderCallBacks.push_back(process); };
		void AddPostProcess(Process process) { m_PostRenderCallBacks.push_back(process); };
		void SetPolygonMode(GLuint nPolygonMode) { m_nPolygonMode = nPolygonMode; }
		void SetLightEnable(GLboolean bOpen) { m_bLightEnable = bOpen; }
		void SetDepthTestEnable(GLboolean bDepthTestEnable) { m_bDepthTestEnable = bDepthTestEnable; }

	protected:
		std::vector<LPtr<GLObject>>::iterator _findGLObject(LPtr<GLObject>& pObject)
		{
			return  std::find(m_GLObjects.begin(), m_GLObjects.end(), pObject);
		}

		LPtr<GLShaderProgram> m_pGLShaderProgram;
		std::vector<LPtr<GLObject>> m_GLObjects;
		std::vector<LPtr<GLLight>> m_lights;

		std::vector<Process> m_PreRenderCallBacks;
		std::vector<Process> m_PostRenderCallBacks;

		GLuint m_nPolygonMode;
		GLboolean m_bLightEnable;
		GLboolean m_bDepthTestEnable;
	};
}