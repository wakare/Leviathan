#pragma once

#include <vector>
#include "LPtr.h"
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

			void RegisterToMainCamera(LPtr<LevCamera> camera, LPtr<LevSceneNode> camera_node);
			LPtr<LevSceneNode> GetMainCameraNode();

			LPtr<LevCamera> GetMainCamera();
			bool SetMainCamera(LPtr<LevCamera> camera);

			bool AddSceneNodeToRoot(LPtr<LevSceneNode> pNode);
			bool AddSceneNodeToParent(LPtr<LevSceneNode> pNode, LPtr<LevSceneNode> parent_node);
			void RemoveAllRenderables();
			void UpdateNodeState();

		private:
			bool m_modified;

			std::function<void(const LevSceneObject&)> m_modifiedCallback;

			LPtr<LevCamera> m_main_camera;
			LPtr<LevSceneNode> m_main_camera_node;

			std::vector<LPtr<LevLight>> m_pLights;
			LPtr<LevSceneTree> m_pSceneTree;
		};
	}
}