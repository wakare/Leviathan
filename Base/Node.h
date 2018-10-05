#pragma once
#include <memory>
#include <vector>
#include "NodeVisitor.h"

template<class T>
class Node
{
public:
	Node(std::shared_ptr<T> pData) : pNodeData(pData) {};
	void AddChild(std::shared_ptr<Node<T>> pChild);
	void DelChild(std::shared_ptr<Node<T>> pChild);
	const std::shared_ptr<T> GetNodeData() { return pNodeData; };
	const std::vector<std::shared_ptr<Node<T>>> GetChildren() { return children; };
	 
	virtual void accept(NodeVisitor<T>& nodeVisitor);

private:
	std::shared_ptr<T> pNodeData;
	std::vector<std::shared_ptr<Node<T>>> children;
};

template<class T>
inline void Node<T>::AddChild(std::shared_ptr<Node<T>> pChild)
{
	children.push_back(pChild);
}

template<class T>
inline void Node<T>::DelChild(std::shared_ptr<Node<T>> pChild)
{
	children.erase(pChild);
}

template<class T>
inline void Node<T>::accept(NodeVisitor<T>& nodeVisitor)
{
	nodeVisitor.apply(*this);
}

