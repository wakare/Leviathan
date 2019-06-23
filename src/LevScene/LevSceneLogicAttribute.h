#pragma once

#include "LevSceneObjectAttribute.h"

namespace Leviathan
{
	namespace Scene
	{
		class LEV_SCENE_API LevSceneLogicAttribute : virtual public LevSceneObjectAttribute
		{
		public:
			LevSceneLogicAttribute();
			virtual ~LevSceneLogicAttribute();
		};
	}
}