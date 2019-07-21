#pragma once

namespace Leviathan
{
	namespace Scene
	{
		enum LevRenderStateType
		{
			ELRST_DEPTH_FUNC,

		};

		class LevRenderState
		{
		public:
			virtual LevRenderStateType GetRenderStateType() const = 0;
		};
	}
}