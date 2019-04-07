#include "OpenGLRenderer.h"
#include "OpenGLPass.h"

namespace Leviathan
{
	namespace Renderer
	{
		OpenGLRenderer::OpenGLRenderer(GLFWwindow* pWindow) :m_pWindow(pWindow), m_bPreInited(false)
		{

		}

		void OpenGLRenderer::PreInit()
		{
			m_bPreInited = true;
		}

		void OpenGLRenderer::Render()
		{
			if (!m_bPreInited) PreInit();

			if (!m_pWindow)
			{
				LogLine("RenderWrapper::Render() --> Render window is invalid");
				return;
			}

			// Set Global state
			glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// Debug
			glPointSize(1);

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

		bool OpenGLRenderer::AddPass(LPtr<OpenGLPass> GLPass)
		{
			auto findResult = std::find(m_GLPasses.begin(), m_GLPasses.end(), GLPass);
			if (findResult != m_GLPasses.end())
			{
				return false;
			}

			m_GLPasses.push_back(GLPass);
			return true;
		}

		bool OpenGLRenderer::DelPass(LPtr<OpenGLPass> GLPass)
		{
			auto findResult = std::find(m_GLPasses.begin(), m_GLPasses.end(), GLPass);
			if (findResult == m_GLPasses.end())
			{
				return false;
			}

			m_GLPasses.erase(findResult);
			return true;
		}

		bool OpenGLRenderer::Clear()
		{
			m_GLPasses.clear();
			return true;
		}

		bool OpenGLRenderer::SetInputData(const Scene::LevSceneData& data)
		{
			return true;
		}

	}
}
