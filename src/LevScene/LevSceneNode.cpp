#include "LevSceneNode.h"
#include "LevSceneObject.h"

namespace Leviathan
{
	namespace Scene
	{
		bool LevSceneNode::HasModified() const
		{
			return m_node_data->HasModified();
		}

		void LevSceneNode::SetModified(bool bRecursion)
		{
			m_node_data->SetModified();

			if (bRecursion)
			{
				for (auto& child : m_children)
				{
					LevSceneNode* pChild = dynamic_cast<LevSceneNode*>(child.Get());
					LEV_ASSERT(pChild);

					pChild->SetModified();
				}
			}
		}

		LevSceneNode::LevSceneNode(LSPtr<LevSceneObject> pSceneNodeData):
			Node<LevSceneObject>(pSceneNodeData)
		{

		}

		Node<LevSceneObject>& LevSceneNode::ToBase()
		{
			return *this;
		}

		void LevSceneNode::AddChild(LSPtr<LevSceneNode> child_node)
		{
			Node<LevSceneObject>::AddChild(child_node.To<Node<LevSceneObject>>());
		}

		void LevSceneNode::DelChild(LSPtr<LevSceneNode> child_node)
		{
			Node<LevSceneObject>::DelChild(child_node.To<Node<LevSceneObject>>());
		}

		void LevSceneNode::SetParent(LSPtr<LevSceneNode> parent_node)
		{
			Node<LevSceneObject>::SetParent(parent_node.To<Node<LevSceneObject>>());
		}
	}
}