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
		void AddDrawableNodeToSceneRenderPass(LPtr<Node<SceneNode>> pBeginNode) const ;
		LPtr<Node<SceneNode>> GetRootNode() const;

	private:
		
		void _addDrawableNodeToSceneOcTree(LPtr<Node<SceneNode>> pBeginNode);
		bool _getAllDrawableNode(LPtr<Node<SceneNode>> pBeginNode, std::vector<LPtr<DrawableNode<SceneNode>>>& outResult);

		LPtr<SceneNodeTraverseVisitor<SceneNode>> m_pSceneNodeTraverseVisitor;
		LPtr<SceneNodeSearchVisitor<SceneNode>> m_pSceneNodeSearchVisitor;

		LPtr<Node<SceneNode>> m_pRoot;
		LPtr<GLPass> m_pSceneRenderPass;
		LPtr<SceneOcTree> m_pSceneOcTree;
	};
}