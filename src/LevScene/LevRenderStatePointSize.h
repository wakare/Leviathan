#pragma once

#include "LevRenderState.h"
#include "LevSceneAPIDefine.h"

namespace Leviathan
{
	namespace Scene
	{
		class LEV_SCENE_API LevRenderStatePointSize : public LevRenderState
		{
		public:
			LevRenderStatePointSize(unsigned point_size);

			LevRenderStateType GetRenderStateType() const override;

			void SetPointSize(unsigned point_size);
			unsigned GetPointSize() const;

		private:
			unsigned m_point_size;
		};
	}
}