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

		class LEV_SCENE_API LevRAttrDepthFunc : public LevSceneRenderAttribute
		{
		public:
			LevRAttrDepthFunc(LevDepthFuncParameter parameter);

			ADD_RENDER_ATTRIBUTE_IMPLEMENT(LevRAttrDepthFunc);

			RenderAttributeType GetRenderAttributeType() const override { return ERAT_DEPTH_FUNC; }

			LevDepthFuncParameter GetDepthParameter() const;

		private:
			LevDepthFuncParameter m_depth_parameter;
		};
	}
}