#include "SceneNodeTraverseVisitor.h"
#include "GLPass.h"

namespace Leviathan
{
	template<class T>
	inline SceneNodeTraverseVisitor<T>::SceneNodeTraverseVisitor(LPtr<GLPass> pSceneRenderPass) :
		m_pSceneRenderPass(pSceneRenderPass),
		m_process(nullptr)
	{

	}

	template<class T>
	inline SceneNodeTraverseVisitor<T>::~SceneNodeTraverseVisitor()
	{
	}

	template<class T>
	inline bool Leviathan::SceneNodeTraverseVisitor<T>::SetTraverseCallback(SceneNodeProcess process)
	{
		m_process = process;
		return true;
	}

	template<class T>
	inline void Leviathan::SceneNodeTraverseVisitor<T>::Apply(Node<T>& node)
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
	inline SceneNodeProcess Leviathan::SceneNodeTraverseVisitor<T>::GetCurrentTraverseCallback()
	{
		return m_process;
	}
}