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

		LevSceneNode::LevSceneNode(LPtr<LevSceneObject> pSceneNodeData):
			Node<LevSceneObject>(pSceneNodeData)
		{

		}

		Node<LevSceneObject>& LevSceneNode::ToBase()
		{
			return *this;
		}
	}
}