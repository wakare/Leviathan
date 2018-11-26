#include "SceneGraph.h"
#include "SceneNodeSearchVisitor.h"
#include "IDrawable.h"

Leviathan::SceneGraph::SceneGraph(LPtr<GLPass> sceneRenderPass):
	m_pSceneNodeTraverseVisitor(nullptr),
	m_pSceneNodeSearchVisitor(nullptr),
	m_pRoot(nullptr),
	m_pSceneRenderPass(sceneRenderPass)
{
	m_pRoot = new Node<SceneNode>(new SceneNode());
	m_pSceneNodeSearchVisitor = new SceneNodeSearchVisitor<SceneNode>();
	m_pSceneNodeTraverseVisitor = new SceneNodeTraverseVisitor<SceneNode>(m_pSceneRenderPass);
}

bool Leviathan::SceneGraph::AddNode(LPtr<Node<SceneNode>> pNode)
{
	if (!pNode)
	{
		LeviathanOutStream << "[ERROR] Add nullptr node." << std::endl;
		return false;
	}

	m_pRoot->AddChild(pNode);
	_addDrawableNodeToSceneRenderPass(pNode);
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

void Leviathan::SceneGraph::_addDrawableNodeToSceneRenderPass(LPtr<Node<SceneNode>> pBeginNode)
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
