#include "NodeVisitor.h"
#include "Node.h"

namespace Leviathan
{
	template<class T>
	NodeVisitor<T>::NodeVisitor(E_TRAVERSE_MODE mode) : m_eTraverseMode(mode) 
	{

	}

	template<class T>
	NodeVisitor<T>::~NodeVisitor()
	{
	}

	template<class T>
	E_TRAVERSE_MODE NodeVisitor<T>::GetTraverseMode()
	{
		return m_eTraverseMode;
	}

	template<class T>
	bool NodeVisitor<T>::SetTraverseMode(E_TRAVERSE_MODE mode)
	{
		m_eTraverseMode = mode; 
		return true;
	}

	template<class T>
	void NodeVisitor<T>::Apply(Node<T>& node)
	{
	}
}
