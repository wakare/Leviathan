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
			m_nodes.push_back(pNode);
		}

		const std::vector<Leviathan::LPtr<Leviathan::Scene::LevSceneNode>>& LevSceneTree::GetNodes()
		{
			return m_nodes;
		}

	}
}