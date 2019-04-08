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

		const std::vector<Leviathan::LPtr<Leviathan::Scene::LevSceneNode>>& LevSceneTree::GetNodes()
		{
			return m_nodes;
		}

	}
}