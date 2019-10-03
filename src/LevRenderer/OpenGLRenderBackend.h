#pragma once

#include "IRendererBackend.h"
#include "LevRendererAPIDefine.h"
#include "OpenGLCommandHandler.h"
#include "LSPtr.h"

namespace Leviathan
{
	class LevOpenGLWindow;

	namespace Renderer
	{
		class OpenGLPass;
		class OpenGLResourceManager;
		class OpenGLRenderDataProcessor;

		class LEV_RENDERER_API OpenGLRenderBackend : public IRendererBackend
		{
		public:
			OpenGLRenderBackend(LevOpenGLWindow& pWindow);
			bool Clear();

			bool SetInputData(const Scene::LevSceneData& data) override;
			void Update() override;

			template<typename LAMBDA_BODY_TYPE>
			bool PushRenderCommand(LAMBDA_BODY_TYPE lambda_body, OpenGLCommandType command_type = EOCT_ASYNC);
			
			bool FlushRenderCommand();

		private:
			bool _push_render_command(LSPtr<IOpenGLCommand> command);

			void _render(OpenGLResourceManager& resource_manager);
			void _renderOneFrame();

			LevOpenGLWindow& m_window;
			LSPtr<OpenGLResourceManager> m_resource_manager;
			LSPtr<OpenGLRenderDataProcessor> m_pRenderData;
			LSPtr<OpenGLCommandHandler> m_command_handler;
		};

		template <typename LAMBDA_BODY_TYPE>
		bool OpenGLRenderBackend::PushRenderCommand(LAMBDA_BODY_TYPE lambda_body, OpenGLCommandType command_type)
		{
			LSPtr<IOpenGLCommand> command = nullptr;
			const bool created = CreateCommand(lambda_body, command_type, command);
			assert(created);

			return _push_render_command(command);
		}

#define ORB_PUSH_SYNC_RENDER_COMMAND(command) PushRenderCommand([&] { command; }, EOCT_SYNC);
#define ORB_PUSH_ASYNC_RENDER_COMMAND(command) PushRenderCommand([&] { command; }, EOCT_ASYNC);
	}
}