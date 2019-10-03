#include "OpenGLRenderStateManager.h"
#include "IOpenGLRenderState.h"
#include "OpenGLRenderBackend.h"

namespace Leviathan
{
	namespace Renderer
	{
		OpenGLRenderStateManager::OpenGLRenderStateManager(OpenGLRenderBackend& render_backend)
			: m_render_backend(render_backend)
		{
			
		}

		void OpenGLRenderStateManager::ApplyRenderState(LSPtr<IOpenGLRenderState> render_state)
		{
			auto it = m_current_render_state.find(render_state->GetRenderStateType());
			if (it != m_current_render_state.end())
			{
				/*
				 * Check whether the same render state
				 */
				if (render_state.Get() == it->second.Get())
				{
					render_state->Apply();
					return;
				}

				render_state->SetLastRenderState(it->second);
				it->second->UnApply();
			}

			render_state->Apply();
			m_current_render_state[render_state->GetRenderStateType()] = render_state;
		}

		bool OpenGLRenderStateManager::FlushRenderCommand()
		{
			return m_render_backend.FlushRenderCommand();
		}
	}
}

