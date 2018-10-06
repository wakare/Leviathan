#pragma once
#include "Node.h"

template <class T> class Node;

template<class T1>
class NodeVisitor
{
public:
	enum class TRAVERSE_MODE
	{
		ALL,
		NONE,
		ONLY,
	};

	NodeVisitor(TRAVERSE_MODE mode = TRAVERSE_MODE::ALL): m_traverseMode(mode) {};
	TRAVERSE_MODE GetTraverseMode() { return m_traverseMode; };
	virtual void apply(Node<T1>& node) {};

private:
	TRAVERSE_MODE m_traverseMode;
};

