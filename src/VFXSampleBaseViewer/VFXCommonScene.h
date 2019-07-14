#pragma once

#include <LevScene.h>
#include "VFXSampleBaseViewerAPIDefine.h"
#include "LevLight.h"
#include "LevCamera.h"
#include "LevNormalScene.h"

namespace Leviathan
{
	using namespace Scene;

	namespace Viewer
	{
		class LEV_VFX_SAMPLE_BASE_VIEWER_API VFXCommonScene : public LevNormalScene
		{
		public:
			VFXCommonScene();
			bool AddLightToLightRootNode(LPtr<Scene::LevLight> light);
			bool SetMainCamera(LPtr<Scene::LevCamera> camera);
		};
	}
}