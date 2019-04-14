
#include "NodeVisitor.h"

namespace Leviathan
{
	template<class T>
	inline void Leviathan::NodeVisitor<T>::Apply(Node<T>& node)
	{
	};


	template<class T>
	inline void Leviathan::NodeVisitor<T>::Apply(const Node<T>& node)
	{

	}

	template<class T>
	inline E_TRAVERSE_MODE Leviathan::NodeVisitor<T>::GetTraverseMode()
	{
		return m_eTraverseMode;
	}

	template<class T>
	inline bool NodeVisitor<T>::SetTraverseMode(E_TRAVERSE_MODE mode)
	{
		m_eTraverseMode = mode; return true;
	}

	template<class T>
	inline Leviathan::NodeVisitor<T>::~NodeVisitor()
	{

	}

	template<class T>
	inline NodeVisitor<T>::NodeVisitor(E_TRAVERSE_MODE mode) : m_eTraverseMode(mode)
	{
	};
}