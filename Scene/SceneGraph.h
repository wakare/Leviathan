#pragma once
#include <functional>
#include "NodeVisitor.h"
#include "SceneNode.h"
#include "SceneNodeSearchVisitor.h"
#include "SceneNodeTraverseVisitor.h"
#include "GLPass.h"

namespace Leviathan
{
	class SceneGraph
	{
	public:
		SceneGraph(LPtr<GLPass> pSceneRenderPass);
		bool AddNode(LPtr<Node<SceneNode>> pNode, bool bAddToPass);
		bool SetSceneNodeTraverseVisitor(LPtr<SceneNodeTraverseVisitor<SceneNode>> pSceneNodeVisitor);
		bool FindFirstMatchNode(std::function<bool(const Node<SceneNode>&)> findFunc, Node<SceneNode>* outResult, LPtr<Node<SceneNode>> beginSearchNode = nullptr);

	private:
		void _addDrawableNodeToSceneRenderPass(LPtr<Node<SceneNode>> pBeginNode);

		LPtr<SceneNodeTraverseVisitor<SceneNode>> m_pSceneNodeTraverseVisitor;
		LPtr<SceneNodeSearchVisitor<SceneNode>> m_pSceneNodeSearchVisitor;

		LPtr<Node<SceneNode>> m_pRoot;
		LPtr<GLPass> m_pSceneRenderPass;
	};
}