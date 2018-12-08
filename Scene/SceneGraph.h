#pragma once
#include <functional>
#include "NodeVisitor.h"
#include "SceneNode.h"
#include "SceneNodeSearchVisitor.h"
#include "SceneNodeTraverseVisitor.h"
#include "GLPass.h"
#include "SceneOcTree.h"

namespace Leviathan
{
	class SceneGraph
	{
	public:
		SceneGraph(LPtr<GLPass> pSceneRenderPass);
		bool AddNode(LPtr<Node<SceneNode>> pNode, bool bAddToPass);
		bool SetSceneNodeTraverseVisitor(LPtr<SceneNodeTraverseVisitor<SceneNode>> pSceneNodeVisitor);
		bool FindFirstMatchNode(std::function<bool(const Node<SceneNode>&)> findFunc, Node<SceneNode>* outResult, LPtr<Node<SceneNode>> beginSearchNode = nullptr);
		void AddDrawableNodeToSceneRenderPass(LPtr<Node<SceneNode>> pBeginNode) ;
		void AddDrawableNodeToSceneOcTree(LPtr<Node<SceneNode>> pBeginNode);
		LPtr<Node<SceneNode>> GetRootNode() const;

	private:
		void _traverseNode(Node<SceneNode>& begin, SceneNodeProcess func);
		bool _getAllSceneNode(LPtr<Node<SceneNode>> pBeginNode, std::vector<Node<SceneNode>*>& outResult);

		LPtr<SceneNodeTraverseVisitor<SceneNode>> m_pSceneNodeTraverseVisitor;
		LPtr<SceneNodeSearchVisitor<SceneNode>> m_pSceneNodeSearchVisitor;

		LPtr<Node<SceneNode>> m_pRoot;
		LPtr<GLPass> m_pSceneRenderPass;
		LPtr<SceneOcTree> m_pSceneOcTree;
	};
}