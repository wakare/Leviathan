#pragma once
#include <functional>
#include "NodeVisitor.h"
#include "SceneNode.h"

namespace Leviathan
{
	typedef std::function<void(Node<SceneNode>&)> SceneNodeProcess;
	class GLPass;

	template<class T>
	class SceneNodeTraverseVisitor : public NodeVisitor<T>
	{
	public:
		SceneNodeTraverseVisitor(LPtr<GLPass> pSceneRenderPass);
		~SceneNodeTraverseVisitor();

		bool SetTraverseCallback(SceneNodeProcess process);
		SceneNodeProcess GetCurrentTraverseCallback();
		void Apply(Node<T>& node);

	private:
		LPtr<GLPass> m_pSceneRenderPass;
		SceneNodeProcess m_process;
	};

}

#include "SceneNodeTraverseVisitor.hpp"