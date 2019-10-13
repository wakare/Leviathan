#pragma once

#include <memory>
#include <vector>
#include <list>
#include "NodeVisitor.h"
#include "LSPtr.h"

namespace Leviathan
{
	template <class T>
	class NodeVisitor;

	template<class T>
	class Node
	{
	public:
		Node(LSPtr<T> pData);
		void AddChild(LSPtr<Node<T>> pChild);
		void DelChild(LSPtr<Node<T>> pChild);
		void DelAllChild();

		void SetParent(LSPtr<Node<T>> parent);
		const LSPtr<Node<T>> GetParent() const;

		const LSPtr<T>& GetNodeData() const { return m_node_data; };
		void SetNodeData(LSPtr<T> pData) { m_node_data.Reset(pData); }

		void SetInvalid() { SetNodeData(nullptr); m_valid = false; }
		bool Invalid() const { return !m_valid; }

		const std::list<LSPtr<Node<T>>>& GetChildren() const { return m_children; };
		std::list<LSPtr<Node<T>>>& GetChildren() { return m_children; };

		virtual ~Node();
		virtual void Accept(NodeVisitor<T>& nodeVisitor);

	protected:
		bool m_valid;
		LSPtr<T> m_node_data;
		//std::vector<LSPtr<Node<T>>> m_children;
		std::list<LSPtr<Node<T>>> m_children;
		LSPtr<Node<T>> m_parent;
	};

	template<class T>
	inline void Leviathan::Node<T>::SetParent(LSPtr<Node<T>> parent)
	{
		m_parent = parent;
	}

	template<class T>
	inline const Leviathan::LSPtr<Leviathan::Node<T>> Leviathan::Node<T>::GetParent() const
	{
		return m_parent;
	}

	template<class T>
	inline Leviathan::Node<T>::Node(LSPtr<T> pData)
		: m_valid(true)
		, m_node_data(pData)
		, m_parent(nullptr)
	{

	}

	template<class T>
	inline Leviathan::Node<T>::~Node()
	{

	}

	template<class T>
	inline void Node<T>::AddChild(LSPtr<Node<T>> pChild)
	{
		m_children.push_back(pChild);
	}

	template<class T>
	inline void Node<T>::DelChild(LSPtr<Node<T>> pChild)
	{
		auto itFind = std::find(m_children.begin(), m_children.end(), pChild);
		if (itFind != m_children.end())
		{
			m_children.erase(itFind);
		}
	}

	template <class T>
	void Node<T>::DelAllChild()
	{
		m_children.clear();
	}

	template<class T>
	inline void Node<T>::Accept(NodeVisitor<T>& nodeVisitor)
	{
		nodeVisitor.Apply(*this);
	}
}