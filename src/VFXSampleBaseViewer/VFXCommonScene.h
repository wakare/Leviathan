#pragma once

#include <LevScene.h>
#include "VFXSampleBaseViewerAPIDefine.h"
#include "LevLight.h"
#include "LevCamera.h"

namespace Leviathan
{
	using namespace Scene;

	namespace Viewer
	{
		class LEV_VFX_SAMPLE_BASE_VIEWER_API VFXCommonScene : public LevScene
		{
		public:
			VFXCommonScene();
			bool AddLight(LPtr<Scene::LevLight> light);
			bool SetCamera(LPtr<Scene::LevCamera> camera);

		private:

		};
	}
}