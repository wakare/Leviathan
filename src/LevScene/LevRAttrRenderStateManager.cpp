#include "LevRAttrRenderStateManager.h"

namespace Leviathan
{
	namespace Scene
	{
		LevRAttrRenderStateManager::LevRAttrRenderStateManager()
			: LevSceneObjectAttribute(ELSOAT_RENDER)
		{
		}

		bool LevRAttrRenderStateManager::UpdateRenderState(LSPtr<LevRenderState> render_state, bool overwrite /*= false*/)
		{
			auto it = m_render_state.find(render_state->GetRenderStateType());
			if (it != m_render_state.end())
			{
				if (overwrite)
				{
					it->second = render_state;
					return true;
				}
				else
				{
					return false;
				}
			}

			m_render_state[render_state->GetRenderStateType()] = render_state;
			return true;
		}

		Leviathan::LSPtr<Leviathan::Scene::LevRenderState> LevRAttrRenderStateManager::GetRenderState(LevRenderStateType state_type)
		{
			auto it = m_render_state.find(state_type);
			if (it != m_render_state.end())
			{
				return it->second;
			}

			return nullptr;
		}

		const std::map<Leviathan::Scene::LevRenderStateType, Leviathan::LSPtr<Leviathan::Scene::LevRenderState>>& LevRAttrRenderStateManager::GetAllRenderState() const
		{
			return m_render_state;
		}

	}
}