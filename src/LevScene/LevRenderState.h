#pragma once

namespace Leviathan
{
	namespace Scene
	{
		enum LevRenderStateType
		{
			ELRST_DEPTH_FUNC,
			ELRST_POINT_SIZE,
		};

		class LevRenderState
		{
		public:
			virtual LevRenderStateType GetRenderStateType() const = 0;
		};
	}
}