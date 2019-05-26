#include "LevRAttrDepthFunc.h"

namespace Leviathan
{
	namespace Scene
	{
		LevRAttrDepthFunc::LevRAttrDepthFunc(LevDepthFuncParameter parameter)
			: LevSceneObjectAttribute(ELSOAT_RENDER)
			, m_depth_parameter(parameter)
		{
		}

		LevDepthFuncParameter LevRAttrDepthFunc::GetDepthParameter() const
		{
			return m_depth_parameter;
		}
	}
}
