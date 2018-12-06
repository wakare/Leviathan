#pragma once
#include "KOcTree.h"
#include "SceneNode.h"
#include "LPtr.h"
#include "GLPass.h"
#include "DrawableNode.h"
#include "GlobalDef.h"

namespace Leviathan
{
	class SceneOcTreeNode : public IOcTreeNode
	{
	public:
		SceneOcTreeNode(const Point3Df& position, LPtr<Node<SceneNode>>& pSceneNode):
			IOcTreeNode(position),
			m_pSceneNode(pSceneNode)
		{

		}

		SceneOcTreeNode(const Point3Df& position, LPtr<DrawableNode<SceneNode>>& pSceneNode) :
			IOcTreeNode(position),
			m_pSceneNode(TryCast<DrawableNode<SceneNode>, Node<SceneNode>>(pSceneNode))
		{
			if (!m_pSceneNode)
			{
				LeviathanOutStream << "[ERROR] pSceneNode is nullptr." << std::endl;
			}
		}

		LPtr<Node<SceneNode>> GetSceneNode()
		{
			return m_pSceneNode;
		}

	private:
		LPtr<Node<SceneNode>>& m_pSceneNode;
	};

	class SceneOcTree
	{
	public:
		SceneOcTree()
		{
			m_pRoot = new KOcTree(nullptr, AABBf());
		}

		bool AddNode(const std::vector<LPtr<IOcTreeNode>>& nodeVec)
		{
			m_pRoot = AddNodeAndUpdateOcTree(m_pRoot, nodeVec);

			return true;
		}

		bool AddAllDrawableNodeToGLPass(LPtr<GLPass>& pGLPass)
		{
			auto _traverseFunc = [&pGLPass](KOcTree& rhs)
			{
				if (!rhs.IsLeaf())
				{
					return;
				}

				auto leadNode = rhs.GetLeafNode();

				auto pSceneNodeOcTreeNode = dynamic_cast<SceneOcTreeNode*>(&(*leadNode));
				if (!pSceneNodeOcTreeNode)
				{
					LeviathanOutStream << "[WARN] Can not cast leafNode to SceneOcTreeNode." << std::endl;
					return;
				}

				auto pSceneNode = pSceneNodeOcTreeNode->GetSceneNode();
				if (!pSceneNode)
				{
					LeviathanOutStream << "[WARN] Can not get sceneNode." << std::endl;
					return;
				}

// 				auto pDrawableSceneNode = TryCast<Node<SceneNode>, DrawableNode<SceneNode>>(pSceneNode);
// 				if (pDrawableSceneNode)
// 				{
// 					LeviathanOutStream << "[WARN] Can not cast sceneNode to drawableNode." << std::endl;
// 					pDrawableSceneNode->RegisterSelfToGLPass(*pGLPass);
// 				}
			};
			
			m_pRoot->Traverse(_traverseFunc, true);

			return true;
		}

	private:
		LPtr<KOcTree> m_pRoot;
	};
}