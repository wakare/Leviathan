#pragma once
#include "LevLight.h"
#include "LevSceneAPIDefine.h"

namespace Leviathan
{
	namespace Scene
	{
		class LEV_SCENE_API LevPointLight : public LevLight
		{
		public:
			LevPointLight(int scene_obj_type);
		};
	}
}