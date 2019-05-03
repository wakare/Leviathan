#include "LevSceneNode.h"
#include "LevSceneObject.h"

namespace Leviathan
{
	namespace Scene
	{
		bool LevSceneNode::HasModified() const
		{
			return pNodeData->HasModified();
		}

		void LevSceneNode::SetModified(bool bRecursion)
		{
			pNodeData->SetModified();

			if (bRecursion)
			{
				for (auto& child : children)
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