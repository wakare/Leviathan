#pragma once
#include "NodeVisitor.h"
#include "SceneNode.h"

namespace Leviathan
{
	template<class T>
	class SceneNodeSearchVisitor : public NodeVisitor<T>
	{
	public:
		SceneNodeSearchVisitor(NodeVisitor::E_TRAVERSE_MODE mode = NodeVisitor::E_TRAVERSE_MODE::ALL) :
			NodeVisitor(mode)
		{

		}

		~SceneNodeSearchVisitor() 
		{

		}

		void Apply(Node<T>& node)
		{
			if (m_findFunc(node))
			{
				*ppOutResult = &node;
				return;
			}

			auto originTraverseMode = m_eTraverseMode;

			switch (m_eTraverseMode)
			{
			case NodeVisitor::E_TRAVERSE_MODE::NONE:
				break;

			case NodeVisitor::E_TRAVERSE_MODE::ONLY:
				m_eTraverseMode = E_TRAVERSE_MODE::NONE;
				node.Accept(*this);
				break;

			case NodeVisitor::E_TRAVERSE_MODE::ALL:
				node.Accept(*this);
				break;

			default:
				break;
			}

			m_eTraverseMode = originTraverseMode;
		}

		bool SetSearchFuncAndOutResult(std::function<bool(const Node<SceneNode>&)> findFunc, Node<SceneNode>** outResult)
		{
			m_findFunc = findFunc;
			ppOutResult = outResult;

			return true;
		}

	private:
		std::function<bool(const Node<SceneNode>&)> m_findFunc;
		Node<SceneNode>** ppOutResult;
	};
}