#pragma once

#include "LSPtr.h"
#include <map>
#include "IOpenGLRenderState.h"
#include "OpenGLRenderBackend.h"

namespace Leviathan
{
	namespace Renderer
	{
		class IOpenGLRenderState;
		class OpenGLRenderBackend;

		class OpenGLRenderStateManager
		{
		public:
			OpenGLRenderStateManager(OpenGLRenderBackend& render_backend);
			void ApplyRenderState(LSPtr<IOpenGLRenderState> render_state);

			template<typename LAMBDA_TYPE>
			bool PushRenderCommand(LAMBDA_TYPE command, OpenGLCommandType type);

			bool FlushRenderCommand();

		private:
			OpenGLRenderBackend& m_render_backend;
			std::map<OpenGLRenderStateType, LSPtr<IOpenGLRenderState>> m_current_render_state;
		}; 
		
		template <typename LAMBDA_TYPE>
			bool OpenGLRenderStateManager::PushRenderCommand(LAMBDA_TYPE command, OpenGLCommandType type)
		{
			m_render_backend.PushRenderCommand(command, type);
			return true;
		}
	}
}
