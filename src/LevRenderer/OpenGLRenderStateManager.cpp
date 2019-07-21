#include "OpenGLRenderStateManager.h"
#include "OpenGLRenderState.h"

namespace Leviathan
{
	namespace Renderer
	{
		OpenGLRenderStateManager::OpenGLRenderStateManager()
		{
		}

		void OpenGLRenderStateManager::AddRenderState(LPtr<OpenGLRenderState> render_state)
		{
			m_render_states.push_back(render_state);
		}

		void OpenGLRenderStateManager::ApplyAllRenderState()
		{
			for (auto& render_state : m_render_states)
			{
				render_state->ApplyState();
			}
		}

		void OpenGLRenderStateManager::UnApplyAllRenderState()
		{
			for (auto& render_state : m_render_states)
			{
				render_state->UnApplyState();
			}
		}
	}
}

