#pragma once
#include "LevSceneData.h"

namespace Leviathan
{
	namespace Renderer
	{
		class IRenderer
		{
		public:
			virtual bool SetInputData(const Scene::LevSceneData& data) = 0;
		};
	}
}
