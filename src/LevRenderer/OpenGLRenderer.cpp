#include "OpenGLRenderer.h"
#include "OpenGLRenderDataProcessor.h"
#include "OpenGLPass.h"
#include "LevOpenGLWindow.h"
#include "OpenGLResourceManager.h"

namespace Leviathan
{
	namespace Renderer
	{
		OpenGLRenderer::OpenGLRenderer(LevOpenGLWindow& pWindow)
			: m_window(pWindow)
			, m_pRenderData(new OpenGLRenderDataProcessor)
		{

		}

		void OpenGLRenderer::_render(OpenGLResourceManager& resource_manager)
		{
			resource_manager.Render();
		}

		void OpenGLRenderer::_renderOneFrame()
		{
			// Set Global state
			glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// Render
			_render(m_pRenderData->GetResourceManager());

			m_window.SwapBuffer();
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
