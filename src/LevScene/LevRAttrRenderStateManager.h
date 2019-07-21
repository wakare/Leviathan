#pragma once
#include "LevSceneRenderAttribute.h"
#include "LPtr.h"
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
			bool UpdateRenderState(LPtr<LevRenderState> render_state, bool overwrite = false);
			LPtr<LevRenderState> GetRenderState(LevRenderStateType state_type);

			const std::map<LevRenderStateType, LPtr<LevRenderState>>& GetAllRenderState() const;

		private:
			std::map<LevRenderStateType, LPtr<LevRenderState>> m_render_state;
		};
	}
}