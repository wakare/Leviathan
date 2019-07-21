#pragma once
#include "LevRenderState.h"
#include "LevSceneAPIDefine.h"

namespace Leviathan
{
	namespace Scene
	{
		enum LevDepthFunc
		{
			ELDF_NEVER,
			ELDF_LESS,
			ELDF_LEQUAL,
			ELDF_EQUAL,
			ELDF_NOTEQUAL,
			ELDF_GEQUAL,
			ELDF_GREATER,
			ELDF_ALWAYS
		};

		class LEV_SCENE_API LevRenderStateDepthFunc : public LevRenderState
		{
		public:
			LevRenderStateDepthFunc(LevDepthFunc depth_func);
			void SetDepthFunc(LevDepthFunc depth_func);
			LevDepthFunc GetDepthFunc() const;

			virtual LevRenderStateType GetRenderStateType() const;

		private:
			LevDepthFunc m_depth_func;
		};
	}
}