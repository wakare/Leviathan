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
			void RegisterToMainCamera(LPtr<LevCamera> pCamera);

			LPtr<LevCamera> GetCamera();

			bool AddSceneNode(LPtr<LevSceneNode> pNode);
			void RemoveAllRenderables();
			void UpdateNodeState();

		private:
			bool m_modified;

			std::function<void(const LevSceneObject&)> m_modifiedCallback;
			LPtr<LevCamera> m_pCamera;
			std::vector<LPtr<LevLight>> m_pLights;
			LPtr<LevSceneTree> m_pSceneTree;
		};

		bool InitCameraAndLight(LevSceneData& scene_data);
	}
}