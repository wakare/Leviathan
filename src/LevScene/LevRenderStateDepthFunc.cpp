#include "LevRenderStateDepthFunc.h"

namespace Leviathan
{
	namespace Scene
	{
		LevRenderStateDepthFunc::LevRenderStateDepthFunc(LevDepthFunc depth_func)
		{
			SetDepthFunc(depth_func);
		}

		void LevRenderStateDepthFunc::SetDepthFunc(LevDepthFunc depth_func)
		{
			m_depth_func = depth_func;
		}

		LevDepthFunc LevRenderStateDepthFunc::GetDepthFunc() const
		{
			return m_depth_func;
		}

		LevRenderStateType LevRenderStateDepthFunc::GetRenderStateType() const
		{
			return ELRST_DEPTH_FUNC;
		}

	}
}