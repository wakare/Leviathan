#pragma once

#include <functional>
#include "NodeVisitor.h"
#include "SceneNode.h"

namespace Leviathan
{
	template<class T>
	class SceneNodeSearchVisitor : public NodeVisitor<T>
	{
	public:
		SceneNodeSearchVisitor(E_TRAVERSE_MODE mode = E_TRAVERSE_MODE::ALL);
		~SceneNodeSearchVisitor();
		void Apply(Node<T>& node);
		bool SetSearchFuncAndOutResult(std::function<bool(const Node<SceneNode>&)> findFunc, Node<SceneNode>** outResult);
		
	private:
		std::function<bool(const Node<SceneNode>&)> m_findFunc;
		Node<SceneNode>** ppOutResult;
	};
	
}

#include "SceneNodeSearchVisitor.hpp"