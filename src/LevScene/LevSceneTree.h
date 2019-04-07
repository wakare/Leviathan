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
			const std::vector<LPtr<LevSceneNode>>& GetNodes();

		private:
			std::vector<LPtr<LevSceneNode>> m_nodes;
		};
	}
}