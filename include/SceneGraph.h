#pragma once
#include <functional>
#include <vector>
#include "LPtr.h"
#include "AABB.h"

namespace Leviathan
{
	template<typename T>
	class Node;

	template<typename T>
	class SceneNodeTraverseVisitor;

	template<typename T>
	class SceneNodeSearchVisitor;

	class GLPass;
	class SceneOcTree;
	class SceneNode;

	typedef std::function<void(Node<SceneNode>&)> SceneNodeProcess;

	class SceneGraph
	{
	public:
		SceneGraph(LPtr<GLPass> pSceneRenderPass);
		bool AddNode(LPtr<Node<SceneNode>> pNode);
		bool SetSceneNodeTraverseVisitor(LPtr<SceneNodeTraverseVisitor<SceneNode>> pSceneNodeVisitor);
		bool FindFirstMatchNode(std::function<bool(const Node<SceneNode>&)> findFunc, Node<SceneNode>* outResult, LPtr<Node<SceneNode>> beginSearchNode = nullptr);
		void AddDrawableNodeToSceneRenderPass(LPtr<Node<SceneNode>> pBeginNode);
		void AddDrawableNodeToSceneOcTree(LPtr<Node<SceneNode>> pBeginNode = nullptr, bool bResursive = true);
		bool AddSceneOcTreeToGLPass();
		AABB GetAABB() const;
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