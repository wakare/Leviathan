#pragma once

#include "LevSceneObjectAttribute.h"

namespace Leviathan
{
	namespace Scene
	{
		class LevSceneRenderAttribute : virtual public LevSceneObjectAttribute
		{
		public:
			LevSceneRenderAttribute();
			virtual ~LevSceneRenderAttribute();
		};
	}
}