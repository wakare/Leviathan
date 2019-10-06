#include "LevUserUpdateVisitor.h"
#include "LevSceneObject.h"
#include <cassert>
#include <Node.h>

namespace Leviathan
{
	namespace Scene
	{
		void LevUserUpdateVisitor::Apply(Node<LevSceneObject>& node)
		{
			if (m_eTraverseMode == NONE)
			{
				return;
			}

			auto& updated_callback = node.GetNodeData()->GetSceneObjectUpdateCallback();
			if (updated_callback)
			{
				updated_callback(*node.GetNodeData());
			}

			if (m_eTraverseMode == ONLY)
			{
				return;
			}

			auto& children = node.GetChildren();
			for (auto& child : children)
			{
				Apply(*child);
			}
		}

		void LevUserUpdateVisitor::Apply(const Node<LevSceneObject>& node)
		{
			assert(false);
		}
	}
}


