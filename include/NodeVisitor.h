#pragma once

namespace Leviathan
{
	template<class T>
	class Node;

	enum E_TRAVERSE_MODE
	{
		ALL,
		NONE,
		ONLY,
	};

	template<class T>
	class NodeVisitor
	{
	public:
		NodeVisitor(E_TRAVERSE_MODE mode = E_TRAVERSE_MODE::ALL);
		virtual ~NodeVisitor();

		E_TRAVERSE_MODE GetTraverseMode();
		bool SetTraverseMode(E_TRAVERSE_MODE mode);

		virtual void Apply(Node<T>& node);
		virtual void Apply(const Node<T>& node);

	protected:
		E_TRAVERSE_MODE m_eTraverseMode;
	};
}

#include "NodeVisitor.hpp"
