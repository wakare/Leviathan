#include "SceneGraph.h"
#include "SceneNodeSearchVisitor.h"
#include "IDrawable.h"

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

bool Leviathan::SceneGraph::AddNode(LPtr<Node<SceneNode>> pNode, bool bAddToPass = false)
{
	if (!pNode)
	{
		LeviathanOutStream << "[ERROR] Add nullptr node." << std::endl;
		return false;
	}

	m_pRoot->AddChild(pNode);

	if (bAddToPass)
	{
		//_addDrawableNodeToSceneRenderPass(pNode);
	}

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
	if (pResult == nullptr)
	{
		return false;
	}

	outResult = pResult;
	return true;
}

void Leviathan::SceneGraph::AddDrawableNodeToSceneRenderPass(LPtr<Node<SceneNode>> pBeginNode) const
{
	auto currentCallback = m_pSceneNodeTraverseVisitor->GetCurrentTraverseCallback();
	auto eCurrentTraverseMode = m_pSceneNodeTraverseVisitor->GetTraverseMode();

	SceneNodeProcess addDrawableToRenderPass = [this](Node<SceneNode>& node)
	{
		auto pDrawable = dynamic_cast<IDrawable*>(&node);
		if (pDrawable)
		{
			pDrawable->RegisterSelfToGLPass(*m_pSceneRenderPass);
		}
	};

	m_pSceneNodeTraverseVisitor->SetTraverseCallback(addDrawableToRenderPass);
	m_pSceneNodeTraverseVisitor->SetTraverseMode(NodeVisitor<SceneNode>::E_TRAVERSE_MODE::ALL);
	m_pSceneNodeTraverseVisitor->Apply(*pBeginNode);

	m_pSceneNodeTraverseVisitor->SetTraverseCallback(currentCallback);
	m_pSceneNodeTraverseVisitor->SetTraverseMode(eCurrentTraverseMode);
}

Leviathan::LPtr<Leviathan::Node<Leviathan::SceneNode>> Leviathan::SceneGraph::GetRootNode() const
{
	return m_pRoot;
}

void Leviathan::SceneGraph::_addDrawableNodeToSceneOcTree(LPtr<Node<SceneNode>> pBeginNode)
{
	std::vector<LPtr<DrawableNode<SceneNode>>> drawableNodeVec;
	if (!_getAllDrawableNode(pBeginNode, drawableNodeVec))
	{
		LeviathanOutStream << "[ERROR] Get all drawable node failed." << std::endl;
		return;
	}

	std::vector<LPtr<IOcTreeNode>> ocTreeNodeVec;
	for (auto& pDrawableNode : drawableNodeVec)
	{
		// Convert drawableNode to ocTreeNode
		auto& coord = pDrawableNode->GetNodeData()->GetWorldCoord();

		LPtr<SceneOcTreeNode> pSceneOcTreeNode = new SceneOcTreeNode(Point3Df(coord.x, coord.y, coord.z), pDrawableNode);
		if (pSceneOcTreeNode)
		{
			ocTreeNodeVec.push_back(TryCast<SceneOcTreeNode, IOcTreeNode>(pSceneOcTreeNode));
			continue;
		}

		LeviathanOutStream << "[ERROR] pSceneOcTree is nullptr." << std::endl;
	}

	m_pSceneOcTree->AddNode(ocTreeNodeVec);
}

bool Leviathan::SceneGraph::_getAllDrawableNode(LPtr<Node<SceneNode>> pBeginNode, std::vector<LPtr<DrawableNode<SceneNode>>>& outResult)
{

	return true;
}
