#pragma once

#include <vector>
#include "LSPtr.h"
#include "LevSceneAPIDefine.h"

namespace Leviathan
{
	namespace Scene
	{
		class LevSceneTree;
		class LevCamera;
		class LevLight;
		class LevSceneNode;
		class LevSceneObject;

		class LEV_SCENE_API LevSceneData
		{
		public:
			LevSceneData();

			LevSceneTree& GetSceneTree();
			const LevSceneTree& GetSceneTree() const;

			bool HasModified() const;
			void SetModified();
			void ResetUnModified();
			void UpdateWorldTransform();
			void UpdateTimer();

			void RegisterToMainCamera(LSPtr<LevCamera> camera, LSPtr<LevSceneNode> camera_node);
			LSPtr<LevCamera> GetMainCamera();
			LSPtr<LevSceneNode> GetMainCameraNode();

			LevSceneNode& GetSceneRootNode();

			bool SetMainCamera(LSPtr<LevCamera> camera);
			bool AddSceneNodeToRoot(LSPtr<LevSceneNode> pNode);
			bool AddSceneNodeToParent(LSPtr<LevSceneNode> pNode, LSPtr<LevSceneNode> parent_node);
			void RemoveAllRenderables();
			void UpdateNodeState();

		protected:
			bool m_modified;

			std::function<void(const LevSceneObject&)> m_modifiedCallback;

			LSPtr<LevCamera> m_main_camera;
			LSPtr<LevSceneNode> m_main_camera_node;

			std::vector<LSPtr<LevLight>> m_pLights;
			LSPtr<LevSceneTree> m_pSceneTree;
		};
	}
}