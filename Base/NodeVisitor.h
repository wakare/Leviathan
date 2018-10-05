#pragma once
#include "Node.h"

//template<class T>
//class NodeVisitor
//{
//public:
//	virtual void apply(T& node) {};
//};

template <class T> class Node;

template<class T1>
class NodeVisitor
{
public:
	virtual void apply(Node<T1>& node) {};
};

