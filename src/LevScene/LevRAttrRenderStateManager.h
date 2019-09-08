#pragma once
#include "LevSceneRenderAttribute.h"
#include "LSPtr.h"
#include "LevRenderState.h"
#include <map>

namespace Leviathan
{
	namespace Scene
	{
		class LEV_SCENE_API LevRAttrRenderStateManager : public LevSceneRenderAttribute
		{
		public:
			LevRAttrRenderStateManager();
			bool UpdateRenderState(LSPtr<LevRenderState> render_state, bool overwrite = false);
			LSPtr<LevRenderState> GetRenderState(LevRenderStateType state_type);

			const std::map<LevRenderStateType, LSPtr<LevRenderState>>& GetAllRenderState() const;

		private:
			std::map<LevRenderStateType, LSPtr<LevRenderState>> m_render_state;
		};
	}
}