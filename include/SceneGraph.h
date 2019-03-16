#pragma once

#include <functional>
#include <vector>
#include "LPtr.h"

class AABB;

namespace Leviathan
{
	class GLPass;
	class SceneOcTree;
	class SceneNode;
	class PickInfo;

	template<typename T>
	class Node;

	template<typename T>
	class SceneNodeTraverseVisitor;

	template<typename T>
	class SceneNodeSearchVisitor;

	typedef std::function<void(Node<SceneNode>&)> SceneNodeProcess;

	class SceneGraph
	{
	public:
		SceneGraph(LPtr<GLPass> pSceneRenderPass);
		bool AddNode(LPtr<Node<SceneNode>> pNode);
		bool AddDrawableNodeToSceneOcTree(LPtr<Node<SceneNode>> pBeginNode = nullptr, bool bResursive = true);
		bool Pick(float* rayPos, float* rayDir, PickInfo& info);
		AABB GetAABB() const;
		SceneOcTree& GetSceneOcTree();
		void Update();

	private:
		void _traverseNode(Node<SceneNode>& begin, SceneNodeProcess func, bool bResursive);
		bool _getAllSceneNode(LPtr<Node<SceneNode>> pBeginNode, std::vector<Node<SceneNode>*>& outResult);
		bool _updateNeedAddNode();

		LPtr<SceneNodeTraverseVisitor<SceneNode>> m_pSceneNodeTraverseVisitor;
		LPtr<SceneNodeSearchVisitor<SceneNode>> m_pSceneNodeSearchVisitor;

		LPtr<Node<SceneNode>> m_pRoot;
		LPtr<GLPass> m_pSceneRenderPass;
		LPtr<SceneOcTree> m_pSceneOcTree;

		std::vector<LPtr<Node<SceneNode>>> m_pNeedAddNodeVec;
	};
}