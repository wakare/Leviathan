#include "RenderWrapper.h"
#include <Algorithm>

namespace Leviathan
{
	void RenderWrapper::PreInit()
	{
		m_bPreInited = true;
	}

	void RenderWrapper::Render()
	{
		if (!m_bPreInited)
		{
			PreInit();
		}

		if (!m_pWindow)
		{
			throw "RenderWrapper::Render() --> Render window is invalid";
			return;
		}

		// Set Global state
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Render subProcess
		for (auto& pGLPass : m_GLPasses)
		{
			if (!pGLPass->Init())
			{
				throw "RenderWrapper::Render() --> GLPass Init failed.";
				return;
			}

			pGLPass->Render();
		}

		glfwSwapBuffers(m_pWindow);
	}

	bool RenderWrapper::AddGLPass(LPtr<GLPass> GLPass)
	{
		auto findResult = std::find(m_GLPasses.begin(), m_GLPasses.end(), GLPass);
		if (findResult != m_GLPasses.end())
		{
			return false;
		}

		m_GLPasses.push_back(GLPass);
		return true;
	}

	bool RenderWrapper::DelGLPass(LPtr<GLPass> GLPass)
	{
		auto findResult = std::find(m_GLPasses.begin(), m_GLPasses.end(), GLPass);
		if (findResult == m_GLPasses.end())
		{
			return false;
		}

		m_GLPasses.erase(findResult);
		return true;
	}
}