#pragma once
#include "KOcTree.h"
#include "SceneNode.h"
#include "LPtr.h"
#include "GLPass.h"
#include "DrawableNode.h"

namespace Leviathan
{
	class SceneNodeOcTreeNode : public ITriDObject
	{
	public:
		SceneNodeOcTreeNode(const Point3Df& position, LPtr<Node<SceneNode>>& pSceneNode):
			ITriDObject(position),
			m_pSceneNode(pSceneNode)
		{

		}

		LPtr<Node<SceneNode>> GetSceneNode()
		{
			return m_pSceneNode;
		}

	private:
		LPtr<Node<SceneNode>>& m_pSceneNode;
	};

	class DrawableNodeOcTree
	{
	public:
		DrawableNodeOcTree()
		{
			m_pRoot = new KOcTree(nullptr, AABBf());
		}

		bool AddNode(const std::vector<LPtr<ITriDObject>>& nodeVec)
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

				auto pSceneNodeOcTreeNode = dynamic_cast<SceneNodeOcTreeNode*>(&(*leadNode));
				if (!pSceneNodeOcTreeNode)
				{
					return;
				}

				auto pSceneNode = pSceneNodeOcTreeNode->GetSceneNode();
				if (!pSceneNode)
				{
					return;
				}

				auto pDrawableSceneNode = TryCast<Node<SceneNode>, DrawableNode<SceneNode>>(pSceneNode);
				if (pDrawableSceneNode)
				{
					pGLPass->AddGLObject(pDrawableSceneNode->GetGLObject());
				}
			};
			
			m_pRoot->Traverse(_traverseFunc, true);

			return true;
		}

	private:
		LPtr<KOcTree> m_pRoot;
	};
}