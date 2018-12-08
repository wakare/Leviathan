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

void Leviathan::SceneGraph::AddDrawableNodeToSceneRenderPass(LPtr<Node<SceneNode>> pBeginNode)
{
	SceneNodeProcess addDrawableToRenderPass = [this](Node<SceneNode>& node)
	{
		auto pDrawable = dynamic_cast<IDrawable*>(&node);
		if (pDrawable)
		{
			pDrawable->RegisterSelfToGLPass(*m_pSceneRenderPass);
		}
	};

	_traverseNode(*pBeginNode, addDrawableToRenderPass);
}

Leviathan::LPtr<Leviathan::Node<Leviathan::SceneNode>> Leviathan::SceneGraph::GetRootNode() const
{
	return m_pRoot;
}

void Leviathan::SceneGraph::AddDrawableNodeToSceneOcTree(LPtr<Node<SceneNode>> pBeginNode)
{
	std::vector<Node<SceneNode>*> sceneNodeVec;
	if (!_getAllSceneNode(pBeginNode, sceneNodeVec))
	{
		LeviathanOutStream << "[ERROR] Get all drawable node failed." << std::endl;
		return;
	}

	std::vector<LPtr<IOcTreeNode>> ocTreeNodeVec;
	for (auto& pSceneNode : sceneNodeVec)
	{
		auto& coord = pSceneNode->GetNodeData()->GetWorldCoord();

		LPtr<SceneOcTreeNode> pSceneOcTreeNode = new SceneOcTreeNode(Point3Df(coord.x, coord.y, coord.z), *pSceneNode);
		if (pSceneOcTreeNode)
		{
			ocTreeNodeVec.push_back(TryCast<SceneOcTreeNode, IOcTreeNode>(pSceneOcTreeNode));
			continue;
		}

		LeviathanOutStream << "[ERROR] pSceneOcTree is nullptr." << std::endl;
	}

	m_pSceneOcTree->AddNode(ocTreeNodeVec);

	m_pSceneOcTree->AddAllDrawableNodeToGLPass(m_pSceneRenderPass);
}

void Leviathan::SceneGraph::_traverseNode(Node<SceneNode>& begin, SceneNodeProcess func)
{
	auto currentCallback = m_pSceneNodeTraverseVisitor->GetCurrentTraverseCallback();
	auto eCurrentTraverseMode = m_pSceneNodeTraverseVisitor->GetTraverseMode();

	m_pSceneNodeTraverseVisitor->SetTraverseCallback(func);
	m_pSceneNodeTraverseVisitor->SetTraverseMode(NodeVisitor<SceneNode>::E_TRAVERSE_MODE::ALL);
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

	_traverseNode(*pBeginNode, _traverseFunc);

	return true;
}
