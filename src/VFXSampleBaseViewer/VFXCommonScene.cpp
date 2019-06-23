#include "VFXCommonScene.h"
#include "LevSceneData.h"
#include "LevSceneNode.h"
#include "LevSceneUtil.h"
#include "LevSceneObject.h"

namespace Leviathan
{
	namespace Viewer
	{
		VFXCommonScene::VFXCommonScene()
			: LevScene()
		{
			Init(LevSceneType::ELST_3D_SCENE);

			// Test Code
			LPtr<LevSceneNode> mesh_node = nullptr;
			auto inited = LevSceneUtil::InitSceneNodeWithMeshFile("D:\\Resource\\Model\\2b\\lufeng.FBX", ELSOT_DYNAMIC, mesh_node);

			if (inited)
			{
				GetSceneData().AddSceneNode(mesh_node);
			}
		}

		bool VFXCommonScene::AddLight(LPtr<Scene::LevLight> light)
		{
			LPtr<Scene::LevSceneNode> m_light_node = new Scene::LevSceneNode(TryCast<Scene::LevLight, Scene::LevSceneObject>(light));
			return GetSceneData().AddSceneNode(m_light_node);
		}

		bool VFXCommonScene::SetCamera(LPtr<Scene::LevCamera> camera)
		{
			return GetSceneData().SetMainCamera(camera);
		}

	}
}