#include "SceneGraph.h"
#include "IDrawable.h"
#include "Node.h"
#include "NodeVisitor.h"
#include "SceneNode.h"
#include "SceneNodeSearchVisitor.h"
#include "SceneNodeTraverseVisitor.h"
#include "GLPass.h"
#include "AABB.h"
#include "SceneOcTree.h"

Leviathan::SceneGraph::SceneGraph(LPtr<GLPass> sceneRenderPass):
	m_pSceneNodeTraverseVisitor(nullptr),
	m_pSceneNodeSearchVisitor(nullptr),
	m_pRoot(nullptr),
	m_pSceneOcTree(nullptr),
	m_pSceneRenderPass(sceneRenderPass)
{
	m_pRoot = new Node<SceneNode>(new SceneNode());
	m_pSceneNodeSearchVisitor = new SceneNodeSearchVisitor<SceneNode>();
	m_pSceneNodeTraverseVisitor = new SceneNodeTraverseVisitor<SceneNode>(m_pSceneRenderPass);
	m_pSceneOcTree = new SceneOcTree();
}

bool Leviathan::SceneGraph::AddNode(LPtr<Node<SceneNode>> pNode)
{
	EXIT_GET_FALSE(pNode);
	m_pNeedAddNodeVec.push_back(pNode);
	return true;
}

bool Leviathan::SceneGraph::SetSceneNodeTraverseVisitor(LPtr<SceneNodeTraverseVisitor<SceneNode>> pSceneNodeVisitor)
{
	m_pSceneNodeTraverseVisitor = pSceneNodeVisitor;
	return true;
}

bool Leviathan::SceneGraph::FindFirstMatchNode(std::function<bool(const Node<SceneNode>&)> findFunc, Node<SceneNode>* outResult, LPtr<Node<SceneNode>> beginSearchNode /*= nullptr*/)
{
	Node<SceneNode>* pResult = nullptr;
	m_pSceneNodeSearchVisitor->SetSearchFuncAndOutResult(findFunc, &pResult);
	m_pSceneNodeSearchVisitor->Apply((beginSearchNode) ? *beginSearchNode : *m_pRoot);
	if (pResult == nullptr) return false; 
	outResult = pResult;
	return true;
}

Leviathan::LPtr<Leviathan::Node<Leviathan::SceneNode>> Leviathan::SceneGraph::GetRootNode() const
{
	return m_pRoot;
}

void Leviathan::SceneGraph::Update()
{
	_updateAllNeedAddNode();
}

bool Leviathan::SceneGraph::AddDrawableNodeToSceneOcTree(LPtr<Node<SceneNode>> pBeginNode /*= nullptr*/, bool bResursive /*= true*/)
{
	pBeginNode = (pBeginNode) ? pBeginNode : m_pRoot;

	std::vector<Node<SceneNode>*> sceneNodeVec;
	if (bResursive && !_getAllSceneNode(pBeginNode, sceneNodeVec))
	{
		LeviathanOutStream << "[ERROR] Get all drawable node failed." << std::endl;
		return false; 
	}
	else
	{
		sceneNodeVec.push_back(pBeginNode.Get());
	}

	std::vector<LPtr<IOcTreeNode>> ocTreeNodeVec;
	for (auto& pSceneNode : sceneNodeVec)
	{
		float worldCoordCenter[3] = { 0.0f };
		EXIT_GET_FALSE(pSceneNode->GetNodeData()->GetWorldCoordCenter(worldCoordCenter));

		LPtr<SceneOcTreeNode> pSceneOcTreeNode = new SceneOcTreeNode(worldCoordCenter, *pSceneNode);
		if (pSceneOcTreeNode)
		{
			ocTreeNodeVec.push_back(TryCast<SceneOcTreeNode, IOcTreeNode>(pSceneOcTreeNode));
			continue;
		}

		LeviathanOutStream << "[ERROR] pSceneOcTree is nullptr." << std::endl;
	}

	EXIT_GET_FALSE(m_pSceneOcTree->AddNode(ocTreeNodeVec));
	return true;
}

bool Leviathan::SceneGraph::AddSceneOcTreeToGLPass()
{
	return AddOcTreeToGLPass(*m_pSceneOcTree, *m_pSceneRenderPass);
}

bool Leviathan::SceneGraph::Pick(float* rayPos, float* rayDir, PickInfo& info)
{
	auto pickFunc = [&info, &rayPos, &rayDir](Node<SceneNode>& node)
	{
		node.GetNodeData()->Pick(rayPos, rayDir, info);
	};

	_traverseNode(*m_pRoot, pickFunc, true);
	return info.pSceneNode != nullptr;
}

Leviathan::AABB Leviathan::SceneGraph::GetAABB() const
{
	return m_pSceneOcTree->GetAABB();
}

void Leviathan::SceneGraph::_traverseNode(Node<SceneNode>& begin, SceneNodeProcess func, bool bResursive)
{
	auto currentCallback = m_pSceneNodeTraverseVisitor->GetCurrentTraverseCallback();
	auto eCurrentTraverseMode = m_pSceneNodeTraverseVisitor->GetTraverseMode();

	m_pSceneNodeTraverseVisitor->SetTraverseCallback(func);
	m_pSceneNodeTraverseVisitor->SetTraverseMode(bResursive ? E_TRAVERSE_MODE::ALL : E_TRAVERSE_MODE::ONLY);
	m_pSceneNodeTraverseVisitor->Apply(begin);

	m_pSceneNodeTraverseVisitor->SetTraverseCallback(currentCallback);
	m_pSceneNodeTraverseVisitor->SetTraverseMode(eCurrentTraverseMode);
}

bool Leviathan::SceneGraph::_getAllSceneNode(LPtr<Node<SceneNode>> pBeginNode, std::vector<Node<SceneNode>*>& outResult)
{
	outResult.clear();
	SceneNodeProcess _traverseFunc = [&outResult](Node<SceneNode>& rhs)
	{
		outResult.push_back(&rhs);
	};

	_traverseNode(*pBeginNode, _traverseFunc, true);
	return true;
}

bool Leviathan::SceneGraph::_updateAllNeedAddNode()
{
	for (auto& node : m_pNeedAddNodeVec)
	{
		m_pRoot->AddChild(node);
		EXIT_GET_FALSE(AddDrawableNodeToSceneOcTree(node, false));
		EXIT_GET_FALSE(m_pSceneOcTree->AddDrawableNodeToGLPass(m_pSceneRenderPass, node));
	}

	m_pNeedAddNodeVec.clear();
	return true;
}
