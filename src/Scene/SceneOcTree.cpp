#include "SceneOcTree.h"
#include "SceneBase.h"

bool Leviathan::AddOcTreeToGLPass(SceneOcTree& OcTree, GLPass& pass)
{
	std::vector<AABBf> pAABBVec;
	OcTree.Traverse([&pAABBVec](KOcTree& rhs)
	{
		pAABBVec.push_back(rhs.GetAABB());
	}, true);

	for (auto& _aabbf : pAABBVec)
	{
		float temp[6] =
		{
			_aabbf.m_min.coord[0],
			_aabbf.m_min.coord[1],
			_aabbf.m_min.coord[2],
			_aabbf.m_max.coord[0],
			_aabbf.m_max.coord[1],
			_aabbf.m_max.coord[2],
		};

		AABB _aabb(temp);
		auto _aabbGLObject = SceneBase::_convertAABBtoGLObject(_aabb);
		_aabbGLObject->SetLightEnable(false);
		pass.AddGLObject(_aabbGLObject);
	}

	return true;
}

Leviathan::SceneOcTree::SceneOcTree()
{
	m_pRoot.reset(new KOcTree(nullptr, AABBf()));
}

bool Leviathan::SceneOcTree::AddNode(std::vector<LPtr<IOcTreeNode>>& nodeVec)
{
	m_pRoot = AddNodeAndUpdateOcTree(std::move(m_pRoot), nodeVec);

	return true;
}

bool Leviathan::SceneOcTree::AddAllDrawableNodeToGLPass(LPtr<GLPass>& pGLPass)
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

	Traverse(_traverseFunc, true);

	return true;
}
void Leviathan::SceneOcTree::Traverse(KOcTree::TraverseFunction traverseFunc, bool bRecursion)
{
	m_pRoot->Traverse(traverseFunc, bRecursion);
}

Leviathan::AABB Leviathan::SceneOcTree::GetAABB() const
{
	auto& _aabb = m_pRoot->GetAABB();
	float coord[6] =
	{
		_aabb.m_min.coord[0],_aabb.m_min.coord[1],_aabb.m_min.coord[2],
		_aabb.m_max.coord[0],_aabb.m_max.coord[1],_aabb.m_max.coord[2],
	};

	return coord;
}

Leviathan::SceneOcTreeNode::SceneOcTreeNode(const Point3Df& position, Node<SceneNode>& sceneNode) :
	IOcTreeNode(position),
	m_sceneNode(sceneNode)
{
}

Leviathan::Node<Leviathan::SceneNode>& Leviathan::SceneOcTreeNode::GetSceneNode()
{
	return m_sceneNode;
}

Leviathan::SceneOcTreeNode::SceneOcTreeNode(const Point3Df& position, DrawableNode<SceneNode>& sceneNode) :
	IOcTreeNode(position),
	m_sceneNode(sceneNode)
{
}
