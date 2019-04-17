#include "LevStateUpdaterVisitor.h"
#include "LevSceneObject.h"
#include "Node.h"

namespace Leviathan
{
	namespace Scene
	{
		LevStateUpdaterVisitor::LevStateUpdaterVisitor(LevStateUpdateCallback updater)
		{
			SetStateUpdateCallback(updater);
		}

		void LevStateUpdaterVisitor::SetStateUpdateCallback(LevStateUpdateCallback updater)
		{
			m_updater = updater;
		}

		void LevStateUpdaterVisitor::Apply(Node<LevSceneObject>& node)
		{
			LEV_ASSERT(m_updater);
			if (m_updater(*node.GetNodeData()))
			{
				for (const auto& child : node.GetChildren())
				{
					child->Accept(*this);
				}
			}
		}

		void LevStateUpdaterVisitor::Apply(const Node<LevSceneObject>& node)
		{
			// Cannot handle const-node
			LEV_ASSERT(false);
		}

	}
}