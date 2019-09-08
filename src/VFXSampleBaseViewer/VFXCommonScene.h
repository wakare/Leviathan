#pragma once

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
			bool AddLightToLightRootNode(LSPtr<Scene::LevLight> light);
			bool SetMainCamera(LSPtr<Scene::LevCamera> camera);
		};
	}
}