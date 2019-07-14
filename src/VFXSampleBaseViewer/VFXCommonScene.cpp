#include "VFXCommonScene.h"
#include "LevSceneData.h"
#include "LevSceneNode.h"
#include "LevSceneUtil.h"
#include "LevSceneObject.h"
#include "LevSceneObjectDescription.h"
#include "LevNormalScene.h"
#include "LevRAttrRenderObjectAttributeBinder.h"
#include "LevMeshObject.h"
#include "LevRAttrUniform.h"
#include "LevTimer.h"
#include "LevRAttrUniformManager.h"

namespace Leviathan
{
	namespace Viewer
	{
		VFXCommonScene::VFXCommonScene()
			: LevNormalScene()
		{
			Init(LevSceneType::ELST_3D_SCENE);
		}

		bool VFXCommonScene::AddLightToLightRootNode(LPtr<Scene::LevLight> light)
		{
			LPtr<Scene::LevSceneNode> m_light_node = new Scene::LevSceneNode(TryCast<Scene::LevLight, Scene::LevSceneObject>(light));
			return GetSceneData().AddSceneNodeToParent(m_light_node, GetLightRootNode());
		}

		bool VFXCommonScene::SetMainCamera(LPtr<Scene::LevCamera> camera)
		{
			return GetSceneData().SetMainCamera(camera);
		}
	}
}