#pragma once

#include "LevOcTree.h"
#include "SceneNode.h"
#include "LPtr.h"
#include "LUPtr.h"
#include "GlobalDef.h"

namespace Leviathan
{
	class SceneNode;
	class GLPass;

	template<typename T>
	class Node;

	class SceneOcTree
	{
	public:
		SceneOcTree(const AABB& aabb);

		const AABB& GetAABB() const;
		bool AddNode(std::vector<Node<SceneNode>*>& nodeVec);
		bool AddAllDrawableNodeToGLPass(LPtr<GLPass>& pGLPass);
		bool AddDrawableNodeToGLPass(LPtr<GLPass>& pGLPass, LPtr<Node<SceneNode>> pNeedAddNode);
		void Traverse(std::function<void(SceneNode&)> traverseFunc, bool bRecursion);

	private:
		LUPtr<LevOcTree<SceneNode>> m_pRoot;
	};

	bool AddOcTreeToGLPass(SceneOcTree& OcTree, GLPass& pass);
}