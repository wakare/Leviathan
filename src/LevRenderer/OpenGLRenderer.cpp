#include "OpenGLRenderer.h"
#include "OpenGLRenderData.h"
#include "OpenGLPass.h"

namespace Leviathan
{
	namespace Renderer
	{
		OpenGLRenderer::OpenGLRenderer(GLFWwindow* pWindow) 
			: m_pWindow(pWindow)
			, m_pRenderData(new OpenGLRenderData)
		{

		}

		void OpenGLRenderer::_renderOneFrame()
		{
			LEV_ASSERT(m_pWindow);

			// Set Global state
			glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// Render
			m_pRenderData->Render();

			glfwSwapBuffers(m_pWindow);
		}

		bool OpenGLRenderer::Clear()
		{
			return true;
		}

		bool OpenGLRenderer::SetInputData(const Scene::LevSceneData& data)
		{
			m_pRenderData->UpdateInputData(data);
			return true;
		}

		void OpenGLRenderer::Update()
		{
			_renderOneFrame();
		}
	}
}
