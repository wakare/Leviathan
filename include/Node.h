#pragma once

#include <memory>
#include <vector>
#include "NodeVisitor.h"
#include "LPtr.h"

namespace Leviathan
{
	template <class T>
	class NodeVisitor;

	template<class T>
	class Node
	{
	public:
		Node(LPtr<T> pData) : pNodeData(pData) {};
		void AddChild(LPtr<Node<T>> pChild);
		void DelChild(LPtr<Node<T>> pChild);
		LPtr<T> GetNodeData() { return pNodeData; };
		const std::vector<LPtr<Node<T>>>& GetChildren() { return children; };

		virtual ~Node();
		virtual void Accept(NodeVisitor<T>& nodeVisitor);

	private:
		LPtr<T> pNodeData;
		std::vector<LPtr<Node<T>>> children;
	};

	template<class T>
	inline Leviathan::Node<T>::~Node()
	{

	}

	template<class T>
	inline void Node<T>::AddChild(LPtr<Node<T>> pChild)
	{
		children.push_back(pChild);
	}

	template<class T>
	inline void Node<T>::DelChild(LPtr<Node<T>> pChild)
	{
		children.erase(pChild);
	}

	template<class T>
	inline void Node<T>::Accept(NodeVisitor<T>& nodeVisitor)
	{
		nodeVisitor.Apply(*this);
	}
}