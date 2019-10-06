#include "LevSceneTreeSearchVisitor.h"
#include "LevSceneObject.h"
#include "Node.h"

namespace Leviathan
{
	namespace Scene
	{
		LevSceneTreeSearchVisitor::LevSceneTreeSearchVisitor(LevSearchCallback searchFunc)
			: m_stopSearch(false)
		{
			SetTraverseCallback(searchFunc);
		}

		void LevSceneTreeSearchVisitor::SetTraverseCallback(LevSearchCallback searchFunc)
		{
			m_searchFunc = searchFunc;
		}

		void LevSceneTreeSearchVisitor::Apply(const Node<LevSceneObject>& node)
		{
			if (m_stopSearch)
			{
				return;
			}

			if (m_eTraverseMode == NONE)
			{
				return;
			}

			LEV_ASSERT(m_searchFunc);
			if (m_searchFunc(*node.GetNodeData(), m_traverseStack, m_stopSearch))
			{
				/*
				 * TODO: Handle traverse_mode is once situation
				 */

				m_traverseStack.push_back(&node);

				for (const auto& child : node.GetChildren())
				{
					child->Accept(*this);
				}

				m_traverseStack.pop_back();
			}

			// Check need reset stopSearch flag
			if (m_traverseStack.empty())
			{
				m_stopSearch = false;
			}
		}

		void LevSceneTreeSearchVisitor::Apply(Node<LevSceneObject>& node)
		{
			if (m_stopSearch)
			{
				return;
			}

			m_traverseStack.push_back(&node);

			LEV_ASSERT(m_searchFunc);
			if (m_searchFunc(*node.GetNodeData(), m_traverseStack, m_stopSearch))
			{
				for (const auto& child : node.GetChildren())
				{
					child->Accept(*this);
				}
			}

			m_traverseStack.pop_back();

			// Check need reset stopSearch flag
			if (m_traverseStack.size() == 0)
			{
				m_stopSearch = false;
			}
		}

	}
}