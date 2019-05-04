#pragma once

#include "LPtr.h"
#include <vector>

namespace Leviathan
{
	namespace Scene
	{
		class LevSceneTree;
		class LevCamera;
		class LevLight;
		class LevSceneNode;
		class LevSceneObject;

		class LevSceneData
		{
		public:
			LevSceneData();

			LevSceneTree& GetSceneTree();
			const LevSceneTree& GetSceneTree() const;

			bool HasModified() const;
			void ResetUnModified();
			void UpdateWorldTransform();

			LPtr<LevCamera> GetCamera();
			LPtr<LevSceneNode> AddCamera(LPtr<LevCamera> pCamera);

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
	}
}