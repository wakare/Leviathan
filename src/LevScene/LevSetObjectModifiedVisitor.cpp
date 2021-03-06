#include "LevSetObjectModifiedVisitor.h"
#include "Node.h"
#include "LevSceneObject.h"

namespace Leviathan
{
	namespace Scene
	{
		void LevSetObjModifiedVisitor::Apply(Node<LevSceneObject>& node)
		{
			if (m_eTraverseMode == NONE)
			{
				return;
			}

			auto& nodeData = node.GetNodeData();
			if (nodeData->HasModified() && (nodeData->GetType() & ELSOT_ONLY_MODIFY_SELF) == 0)
			{
				if (m_eTraverseMode == ONLY)
				{
					return;
				}

				// Set child modified flag
				for (auto& child : node.GetChildren())
				{
					child->GetNodeData()->SetModified();
				}
			}

			for (auto& child : node.GetChildren())
			{
				child->Accept(*this);
			}
		}

		void LevSetObjModifiedVisitor::Apply(const Node<LevSceneObject>& node)
		{
			LEV_ASSERT(false);
		}

	}
}