#pragma once
#include "LevSceneRenderAttribute.h"

namespace Leviathan
{
	namespace Scene
	{
		enum LevDepthFuncParameter
		{
			ELDFP_LESS,
			ELDFP_LEQUAL,
			ELDFP_EQUAL,
			ELDFP_ALWAYS,
			ELDFP_UNKNOWN,
		};

		class LevRAttrDepthFunc : public LevSceneRenderAttribute
		{
		public:
			LevRAttrDepthFunc(LevDepthFuncParameter parameter);
			LevDepthFuncParameter GetDepthParameter() const;

		private:
			LevDepthFuncParameter m_depth_parameter;
		};
	}
}