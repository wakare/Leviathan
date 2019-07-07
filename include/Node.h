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
		Node(LPtr<T> pData);
		void AddChild(LPtr<Node<T>> pChild);
		void DelChild(LPtr<Node<T>> pChild);

		void SetParent(LPtr<Node<T>> parent);
		const LPtr<Node<T>> GetParent() const;

		const LPtr<T>& GetNodeData() const { return m_node_data; };
		void SetNodeData(LPtr<T> pData) { m_node_data.Reset(pData); }

		void SetInvalid() { SetNodeData(nullptr); }
		bool Invalid() const { return m_node_data.Get(); }

		const std::vector<LPtr<Node<T>>>& GetChildren() const { return m_children; };
		std::vector<LPtr<Node<T>>>& GetChildren() { return m_children; };

		virtual ~Node();
		virtual void Accept(NodeVisitor<T>& nodeVisitor);

	protected:
		LPtr<T> m_node_data;
		std::vector<LPtr<Node<T>>> m_children;
		LPtr<Node<T>> m_parent;
	};

	template<class T>
	inline void Leviathan::Node<T>::SetParent(LPtr<Node<T>> parent)
	{
		m_parent = parent;
	}

	template<class T>
	inline const Leviathan::LPtr<Leviathan::Node<T>> Leviathan::Node<T>::GetParent() const
	{
		return m_parent;
	}

	template<class T>
	inline Leviathan::Node<T>::Node(LPtr<T> pData)
		: m_node_data(pData)
		, m_parent(nullptr)
	{

	}

	template<class T>
	inline Leviathan::Node<T>::~Node()
	{

	}

	template<class T>
	inline void Node<T>::AddChild(LPtr<Node<T>> pChild)
	{
		m_children.push_back(pChild);
	}

	template<class T>
	inline void Node<T>::DelChild(LPtr<Node<T>> pChild)
	{
		auto itFind = std::find(m_children.begin(), m_children.end(), pChild);
		if (itFind != m_children.end())
		{
			m_children.erase(itFind);
		}
	}

	template<class T>
	inline void Node<T>::Accept(NodeVisitor<T>& nodeVisitor)
	{
		nodeVisitor.Apply(*this);
	}
}