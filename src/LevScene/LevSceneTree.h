#pragma once

#include <vector>
#include "LPtr.h"

namespace Leviathan
{
	namespace Scene
	{
		class LevSceneNode;

		class LevSceneTree
		{
		public:
			LevSceneTree();
			bool AddNode(LPtr<LevSceneNode> pNode);
			
			std::vector<LPtr<LevSceneNode>>& GetNodes();
			const std::vector<LPtr<LevSceneNode>>& GetNodes() const;


		private:
			std::vector<LPtr<LevSceneNode>> m_nodes;
		};
	}
}