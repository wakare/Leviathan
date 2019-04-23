#pragma once

#include "LevSceneObjectAttribute.h"

namespace Leviathan
{
	namespace Scene
	{
		class LevSceneLogicAttribute : virtual public LevSceneObjectAttribute
		{
		public:
			LevSceneLogicAttribute();
			virtual ~LevSceneLogicAttribute();
		};
	}
}