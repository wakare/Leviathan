#include "OpenGLRenderStateManager.h"
#include "IOpenGLRenderState.h"

namespace Leviathan
{
	namespace Renderer
	{
		OpenGLRenderStateManager::OpenGLRenderStateManager()
		= default;

		void OpenGLRenderStateManager::ApplyRenderState(LPtr<IOpenGLRenderState> render_state)
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

	}
}

