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

		class LevSceneData
		{
		public:
			LevSceneData();

			LevSceneTree& GetSceneTree();
			const LevSceneTree& GetSceneTree() const;

			bool HasModified() const;
			void SetModified();
			void ResetModified();

			LPtr<LevCamera> GetCamera();
			bool SetCamera(LPtr<LevCamera> pCamera);

			const std::vector<LPtr<LevLight>> GetLights() const;
			bool AddLight(LPtr<LevLight> pLight);

			bool AddSceneNode(LPtr<LevSceneNode> pNode);

		private:
			bool m_modified;
			
			LPtr<LevCamera> m_pCamera;
			std::vector<LPtr<LevLight>> m_pLights;
			LPtr<LevSceneTree> m_pSceneTree;
		};
	}
}