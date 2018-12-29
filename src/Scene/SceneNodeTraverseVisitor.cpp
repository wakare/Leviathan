#include "SceneNodeTraverseVisitor.h"
#include "GLPass.h"

namespace Leviathan
{
	template<class T>
	SceneNodeTraverseVisitor<T>::SceneNodeTraverseVisitor(LPtr<GLPass> pSceneRenderPass) :
		m_pSceneRenderPass(pSceneRenderPass),
		m_process(nullptr)
	{

	}

	template<class T>
	SceneNodeTraverseVisitor<T>::~SceneNodeTraverseVisitor()
	{
	}

	template<class T>
	bool Leviathan::SceneNodeTraverseVisitor<T>::SetTraverseCallback(SceneNodeProcess process)
	{
		m_process = process;
		return true;
	}

	template<class T>
	void Leviathan::SceneNodeTraverseVisitor<T>::Apply(Node<T>& node)
	{
		if (m_process)
		{
			m_process(node);
		}

		auto originTraverseMode = m_eTraverseMode;
		auto children = node.GetChildren();

		switch (m_eTraverseMode)
		{
		case E_TRAVERSE_MODE::NONE:
			break;

		case E_TRAVERSE_MODE::ONLY:
			m_eTraverseMode = E_TRAVERSE_MODE::NONE;
			for (auto pChildren : children)
			{
				pChildren->Accept(*this);
			}
			break;

		case E_TRAVERSE_MODE::ALL:
			for (auto pChildren : children)
			{
				pChildren->Accept(*this);
			}

			break;

		default:
			break;
		}

		m_eTraverseMode = originTraverseMode;
	}

	template<class T>
	SceneNodeProcess Leviathan::SceneNodeTraverseVisitor<T>::GetCurrentTraverseCallback()
	{
		return m_process;
	}
}