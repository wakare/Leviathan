#include "OpenGLRenderBackend.h"
#include <utility>
#include "OpenGLRenderDataProcessor.h"
#include "OpenGLPass.h"
#include "LevOpenGLWindow.h"
#include "OpenGLResourceManager.h"
#include "OpenGLCommandHandler.h"

namespace Leviathan
{
	namespace Renderer
	{
		OpenGLRenderBackend::OpenGLRenderBackend(LevOpenGLWindow& pWindow)
			: m_window(pWindow)
			, m_resource_manager(new OpenGLResourceManager(*this))
			, m_pRenderData(new OpenGLRenderDataProcessor(*m_resource_manager))
			, m_command_handler(new OpenGLCommandHandler(EOCHT_NON_EXTRA_THREAD))
		{

		}

		void OpenGLRenderBackend::_render(OpenGLResourceManager& resource_manager)
		{
			resource_manager.Render();
		}

		void OpenGLRenderBackend::_renderOneFrame()
		{
			// Set Global state
			ORB_PUSH_ASYNC_RENDER_COMMAND(glClearColor(0.3f, 0.3f, 0.3f, 1.0f);)
			ORB_PUSH_ASYNC_RENDER_COMMAND(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);)

			// Render
			_render(*m_resource_manager);

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

		bool OpenGLRenderBackend::FlushRenderCommand()
		{
			return m_command_handler->FlushBuffer();
		}

		bool OpenGLRenderBackend::_push_render_command(LSPtr<IOpenGLCommand> command)
		{
			return m_command_handler->PushCommand(std::move(command));
		}
	}
}
