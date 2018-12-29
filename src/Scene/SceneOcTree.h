#pragma once
#include "KOcTree.h"
#include "SceneNode.h"
#include "LPtr.h"
#include "LUPtr.h"
#include "GLPass.h"
#include "DrawableNode.h"
#include "GlobalDef.h"

namespace Leviathan
{
	class SceneOcTreeNode : public IOcTreeNode
	{
	public:
		SceneOcTreeNode(const Point3Df& position, Node<SceneNode>& sceneNode);
		SceneOcTreeNode(const Point3Df& position, DrawableNode<SceneNode>& sceneNode);

		Node<SceneNode>& GetSceneNode();

	private:
		Node<SceneNode>& m_sceneNode;
	};

	class SceneOcTree
	{
	public:
		SceneOcTree();

		bool AddNode(std::vector<LPtr<IOcTreeNode>>& nodeVec);
		bool AddAllDrawableNodeToGLPass(LPtr<GLPass>& pGLPass);
		void Traverse(KOcTree::TraverseFunction traverseFunc, bool bRecursion);
		AABB GetAABB() const;

	private:
		LUPtr<KOcTree> m_pRoot;
	};

	bool AddOcTreeToGLPass(SceneOcTree& OcTree, GLPass& pass);
}