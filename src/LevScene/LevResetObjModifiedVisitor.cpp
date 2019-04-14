#include "LevResetObjModifiedVisitor.h"
#include "LevSceneObject.h"
#include "Node.h"

namespace Leviathan
{
	namespace Scene
	{
		void LevResetObjModifiedVisitor::Apply(Node<LevSceneObject>& node)
		{
			auto& nodeData = node.GetNodeData();
			if ((nodeData->GetType() & ELSOT_NOT_MODIFY) > 0)
			{
				return;
			}
			
			nodeData->ResetModified();

			for (auto& child : node.GetChildren())
			{
				child->Accept(*this);
			}
		}

		void LevResetObjModifiedVisitor::Apply(const Node<LevSceneObject>& node)
		{
			LEV_ASSERT(false);
		}

	}
}