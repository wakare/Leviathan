#include "LevCalculateWorldCoordVisitor.h"
#include "LevSceneobject.h"
#include "Node.h"

namespace Leviathan
{
	namespace Scene
	{
		void LevCalculateWorldCoordVisitor::Apply(Node<LevSceneObject>& node)
		{
			if (m_eTraverseMode == NONE)
			{
				return;
			}

			Eigen::Matrix4f curWorldTransform = Eigen::Matrix4f::Identity();
			if (!m_stack.empty())
			{
				curWorldTransform = m_stack[m_stack.size() - 1];
			}
			
			auto& nodeData = node.GetNodeData();
			if (nodeData->HasModified() && nodeData->NeedRecalculateWorldTransform())
			{
				curWorldTransform = curWorldTransform * nodeData->GetLocalTransform();
				nodeData->SetWorldTransform(curWorldTransform);
			}

			if (m_eTraverseMode == ONLY)
			{
				return;
			}

			m_stack.push_back(nodeData->GetWorldTransform());
			
			for (auto& pChild : node.GetChildren())
			{
				pChild->Accept(*this);
			}

			m_stack.pop_back();
		}

		void LevCalculateWorldCoordVisitor::Apply(const Node<LevSceneObject>& node)
		{
			LEV_ASSERT(false);
		}

	}
}