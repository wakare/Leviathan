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
		SceneOcTreeNode(const Point3Df& position, Node<SceneNode>& sceneNode):
			IOcTreeNode(position),
			m_sceneNode(sceneNode)
		{
		}

		SceneOcTreeNode(const Point3Df& position, DrawableNode<SceneNode>& sceneNode) :
			IOcTreeNode(position),
			m_sceneNode(sceneNode)
		{
		}

		Node<SceneNode>& GetSceneNode()
		{
			return m_sceneNode;
		}

	private:
		Node<SceneNode>& m_sceneNode;
	};

	class SceneOcTree
	{
	public:
		SceneOcTree()
		{
			m_pRoot.reset(new KOcTree(nullptr, AABBf()));
		}

		bool AddNode(std::vector<LPtr<IOcTreeNode>>& nodeVec)
		{
			m_pRoot = AddNodeAndUpdateOcTree(std::move(m_pRoot), nodeVec);

			return true;
		}

		bool AddAllDrawableNodeToGLPass(LPtr<GLPass>& pGLPass)
		{
			KOcTree::TraverseFunction _traverseFunc = [&pGLPass](KOcTree& rhs)
			{
				if (!rhs.IsLeaf())
				{
					return;
				}

				auto leafNodeVec = rhs.GetLeafNodeVec();

				for (auto leafNode : leafNodeVec)
				{
					auto pSceneNodeOcTreeNode = dynamic_cast<SceneOcTreeNode*>(&(*leafNode));
					if (!pSceneNodeOcTreeNode)
					{
						LeviathanOutStream << "[WARN] Can not cast leafNode to SceneOcTreeNode." << std::endl;
						return;
					}

					auto& sceneNode = pSceneNodeOcTreeNode->GetSceneNode();
					DrawableNode<SceneNode>* pDrawableNode = dynamic_cast<DrawableNode<SceneNode>*>(&sceneNode);

					if (pDrawableNode)
					{
						pDrawableNode->RegisterSelfToGLPass(*pGLPass);
					}
				}
			};
			
			m_pRoot->Traverse(_traverseFunc, true);

			return true;
		}

	private:
		LUPtr<KOcTree> m_pRoot;
	};
}