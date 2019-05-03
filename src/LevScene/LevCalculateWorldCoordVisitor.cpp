#include "LevCalculateWorldCoordVisitor.h"
#include "LevSceneobject.h"
#include "Node.h"

namespace Leviathan
{
	namespace Scene
	{
		void LevCalculateWorldCoordVisitor::Apply(Node<LevSceneObject>& node)
		{
			Eigen::Matrix4f curWorldTransform = Eigen::Matrix4f::Identity();
			if (m_stack.size() > 0)
			{
				curWorldTransform = m_stack[m_stack.size() - 1];
			}
			
			auto& nodeData = node.GetNodeData();
			curWorldTransform = nodeData->GetLocalTransform() * curWorldTransform;
			nodeData->SetWorldTransform(curWorldTransform);

			m_stack.push_back(curWorldTransform);

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