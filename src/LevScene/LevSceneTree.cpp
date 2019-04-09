#include "LevSceneTree.h"
#include "LevSceneNode.h"

namespace Leviathan
{
	namespace Scene
	{
		LevSceneTree::LevSceneTree()
		{

		}

		bool LevSceneTree::AddNode(LPtr<LevSceneNode> pNode)
		{
			if (!pNode)
			{
				return false;
			}

			m_nodes.push_back(pNode);
			return true;
		}

		std::vector<LPtr<LevSceneNode>>& LevSceneTree::GetNodes()
		{
			return m_nodes;
		}

		const std::vector<Leviathan::LPtr<Leviathan::Scene::LevSceneNode>>& LevSceneTree::GetNodes() const
		{
			return m_nodes;
		}

	}
}