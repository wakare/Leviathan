#include "OpenGLRenderBackend.h"
#include "OpenGLRenderDataProcessor.h"
#include "OpenGLPass.h"
#include "LevOpenGLWindow.h"
#include "OpenGLResourceManager.h"

namespace Leviathan
{
	namespace Renderer
	{
		OpenGLRenderBackend::OpenGLRenderBackend(LevOpenGLWindow& pWindow)
			: m_window(pWindow)
			, m_pRenderData(new OpenGLRenderDataProcessor)
		{

		}

		void OpenGLRenderBackend::_render(OpenGLResourceManager& resource_manager)
		{
			resource_manager.Render();
		}

		void OpenGLRenderBackend::_renderOneFrame()
		{
			// Set Global state
			glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// Render
			_render(m_pRenderData->GetResourceManager());

			m_window.SwapBuffer();
		}

		bool OpenGLRenderBackend::Clear()
		{
			return true;
		}

		bool OpenGLRenderBackend::SetInputData(const Scene::LevSceneData& data)
		{
			m_pRenderData->UpdateInputData(data);
			return true;
		}

		void OpenGLRenderBackend::Update()
		{
			_renderOneFrame();
		}
	}
}
