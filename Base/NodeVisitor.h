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
		enum class TRAVERSE_MODE
		{
			ALL,
			NONE,
			ONLY,
		};

		NodeVisitor(TRAVERSE_MODE mode = TRAVERSE_MODE::ALL) : m_eTraverseMode(mode) {};
		TRAVERSE_MODE GetTraverseMode() { return m_eTraverseMode; };
		virtual void apply(Node<T>& node) {};

	private:
		TRAVERSE_MODE m_eTraverseMode;
	};
}
