#pragma once

#include "LevSceneObjectAttribute.h"

namespace Leviathan
{
	namespace Scene
	{
		class LEV_SCENE_API LevSceneRenderAttribute : virtual public LevSceneObjectAttribute
		{
		public:
			LevSceneRenderAttribute();
			virtual ~LevSceneRenderAttribute();
		};
	}
}