#include "LevSceneTreeTraverseVisitor.h"
#include "LevSceneObject.h"
#include "Node.h"

namespace Leviathan
{
	namespace Scene
	{

		LevSceneTreeTraverseVisitor::LevSceneTreeTraverseVisitor(LevTraverseCallback func)
		{
			SetTraverseCallback(func);
		}

		void LevSceneTreeTraverseVisitor::SetTraverseCallback(LevTraverseCallback func)
		{
			m_traverseCallback = func;
		}

		void LevSceneTreeTraverseVisitor::Apply(const Node<LevSceneObject>& node)
		{
			if (m_eTraverseMode == NONE)
			{
				return;
			}

			LEV_ASSERT(m_traverseCallback);

			if (m_traverseCallback(*node.GetNodeData(), m_traverseStack))
			{
				if (m_eTraverseMode == ONLY)
				{
					return;
				}

				m_traverseStack.push_back(&node);

				for (const auto& child : node.GetChildren())
				{
					child->Accept(*this);
				}

				m_traverseStack.pop_back();
			}
		}

		void LevSceneTreeTraverseVisitor::Apply(Node<LevSceneObject>& node)
		{
			if (m_eTraverseMode == NONE)
			{
				return;
			}

			LEV_ASSERT(m_traverseCallback);

			if (m_traverseCallback(*node.GetNodeData(), m_traverseStack))
			{
				if (m_eTraverseMode == ONLY)
				{
					return;
				}

				m_traverseStack.push_back(&node);

				for (const auto& child : node.GetChildren())
				{
					child->Accept(*this);
				}

				m_traverseStack.pop_back();
			}
		}

	}
}