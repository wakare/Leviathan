#pragma once
#include <functional>
#include "NodeVisitor.h"

namespace Leviathan
{
	template<class T>
	class SceneNodeTraverseVisitor : public NodeVisitor<T>
	{
	public:
		typedef std::function<void(Node<SceneNode>&)> SceneNodeProcess;

		SceneNodeTraverseVisitor(LPtr<GLPass> pSceneRenderPass):
			m_pSceneRenderPass(pSceneRenderPass),
			m_process(nullptr)
		{

		}

		~SceneNodeTraverseVisitor()
		{

		}

		bool SetTraverseCallback(SceneNodeProcess process);
		SceneNodeProcess GetCurrentTraverseCallback();
		void Apply(Node<T>& node);

	private:
		LPtr<GLPass> m_pSceneRenderPass;
		SceneNodeProcess m_process;
	};

	template<class T>
	SceneNodeProcess Leviathan::SceneNodeTraverseVisitor<T>::GetCurrentTraverseCallback()
	{
		return m_process;
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

		switch (m_eTraverseMode)
		{
		case NodeVisitor::E_TRAVERSE_MODE::NONE:
			break;

		case NodeVisitor::E_TRAVERSE_MODE::ONLY:
			m_eTraverseMode = E_TRAVERSE_MODE::NONE;
			node.Accept(*this);
			break;

		case NodeVisitor::E_TRAVERSE_MODE::ALL:
			node.Accept(*this);
			break;

		default:
			break;
		}

		m_eTraverseMode = originTraverseMode;
	}
}