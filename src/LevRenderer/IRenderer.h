#pragma once
#include "LevSceneData.h"
#include "LevRendererAPIDefine.h"

namespace Leviathan
{
	namespace Renderer
	{
		class LEV_RENDERER_API IRenderer
		{
		public:
			virtual bool SetInputData(const Scene::LevSceneData& data) = 0;
			virtual void Update() = 0;
		};
	}
}
