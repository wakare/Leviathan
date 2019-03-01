#include "SceneOcTree.h"
#include "SceneHelper.h"
#include "GlobalDef.h"
#include "GLPass.h"
#include "DrawableNode.h"
#include "SceneNode.h"
#include "AABB.h"

namespace Leviathan
{
	bool AddOcTreeToGLPass(SceneOcTree& OcTree, GLPass& pass)
	{
		return true;
	}

	SceneOcTree::SceneOcTree(const AABB& aabb)
	{
		m_pRoot.reset(new LOcTree<SceneNode>(aabb));
	}

	bool SceneOcTree::AddNode(std::vector<Node<SceneNode>*>& nodeVec)
	{
		for (auto& pNode : nodeVec)
		{
			AABB _aabb; pNode->GetNodeData()->GetAABB(_aabb);
			m_pRoot->AddData(pNode->GetNodeData().Get(), _aabb);
		}

		return true;
	}

	bool SceneOcTree::AddAllDrawableNodeToGLPass(LPtr<GLPass>& pGLPass)
	{
		auto& dataVec = m_pRoot->GetDataVec();
		for (auto& data : dataVec)
		{
			DrawableNode<SceneNode>* pDrawableNode = dynamic_cast<DrawableNode<SceneNode>*>(data);
			if (pDrawableNode) pDrawableNode->RegisterSelfToGLPass(*pGLPass);
		}

		return true;
	}

	bool SceneOcTree::AddDrawableNodeToGLPass(LPtr<GLPass>& pGLPass, LPtr<Node<SceneNode>> pNeedAddNode)
	{
		DrawableNode<SceneNode>& drawableNode = dynamic_cast<DrawableNode<SceneNode>&> (*pNeedAddNode);
		EXIT_GET_FALSE(drawableNode.RegisterSelfToGLPass(*pGLPass));
		return true;
	}

	void SceneOcTree::Traverse(std::function<void(SceneNode&)> traverseFunc, bool bRecursion)
	{
		m_pRoot->Traverse(traverseFunc, bRecursion);
	}

	const AABB& SceneOcTree::GetAABB() const
	{
		return m_pRoot->GetAABB();
	}
}