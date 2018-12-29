#include "SceneNodeSearchVisitor.h"

namespace Leviathan
{
	template<class T>
	SceneNodeSearchVisitor<T>::SceneNodeSearchVisitor(E_TRAVERSE_MODE mode)
	{
	}

	template<class T>
	SceneNodeSearchVisitor<T>::~SceneNodeSearchVisitor()
	{
	}
	template<class T>
	void SceneNodeSearchVisitor<T>::Apply(Node<T>& node)

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
	template<class T>
	bool SceneNodeSearchVisitor<T>::SetSearchFuncAndOutResult(std::function<bool(const Node<SceneNode>&)> findFunc, Node<SceneNode>** outResult) {
		m_findFunc = findFunc;
		ppOutResult = outResult;

		return true;
	}
}