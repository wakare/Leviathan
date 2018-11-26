#pragma once
#include "Node.h"

namespace Leviathan
{
	template<class T>
	class Node;

	template<class T>
	class NodeVisitor
	{
	public:
		enum class E_TRAVERSE_MODE
		{
			ALL,
			NONE,
			ONLY,
		};

		NodeVisitor(E_TRAVERSE_MODE mode = E_TRAVERSE_MODE::ALL) : m_eTraverseMode(mode) {};
		virtual ~NodeVisitor() {};

		E_TRAVERSE_MODE GetTraverseMode() { return m_eTraverseMode; };
		bool SetTraverseMode(E_TRAVERSE_MODE mode) { m_eTraverseMode = mode; return true; }

		virtual void Apply(Node<T>& node) {};

	protected:
		E_TRAVERSE_MODE m_eTraverseMode;
	};
}
