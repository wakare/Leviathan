#include "SceneGraph.h"
#include "IDrawable.h"
#include "Node.h"
#include "NodeVisitor.h"
#include "SceneNode.h"
#include "SceneNodeSearchVisitor.h"
#include "SceneNodeTraverseVisitor.h"
#include "GLPass.h"
#include "SceneOcTree.h"

namespace Leviathan
{
	 SceneGraph::SceneGraph(LPtr<GLPass> sceneRenderPass) :
		m_pSceneNodeTraverseVisitor(nullptr),
		m_pSceneNodeSearchVisitor(nullptr),
		m_pRoot(nullptr),
		m_pSceneOcTree(nullptr),
		m_pSceneRenderPass(sceneRenderPass)
	{
		m_pRoot = new Node<SceneNode>(new SceneNode());
		m_pSceneNodeSearchVisitor = new SceneNodeSearchVisitor<SceneNode>();
		m_pSceneNodeTraverseVisitor = new SceneNodeTraverseVisitor<SceneNode>(m_pSceneRenderPass);
		float aabbValue[6] = { -10000.0f, -10000.0f, -10000.0f, 10000.0f, 10000.0f, 10000.0f };
		AABB sceneAABB(aabbValue, aabbValue + 3);
		m_pSceneOcTree = new SceneOcTree(sceneAABB);
	}

	bool  SceneGraph::AddNode(LPtr<Node<SceneNode>> pNode)
	{
		EXIT_IF_FALSE(pNode);
		m_pNeedAddNodeVec.push_back(pNode);
		return true;
	}

	void  SceneGraph::Update()
	{
		_updateNeedAddNode();
	}

	bool  SceneGraph::AddDrawableNodeToSceneOcTree(LPtr<Node<SceneNode>> pBeginNode /*= nullptr*/, bool bResursive /*= true*/)
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

		EXIT_IF_FALSE(m_pSceneOcTree->AddNode(sceneNodeVec));
		return true;
	}

	bool  SceneGraph::Pick(float* rayPos, float* rayDir, PickInfo& info)
	{
		auto pickFunc = [&info, &rayPos, &rayDir](Node<SceneNode>& node)
		{
			node.GetNodeData()->Pick(rayPos, rayDir, info);
		};

		_traverseNode(*m_pRoot, pickFunc, true);
		return info.pSceneNode != nullptr;
	}

	AABB  SceneGraph::GetAABB() const
	{
		return m_pSceneOcTree->GetAABB();
	}

	SceneOcTree &  SceneGraph::GetSceneOcTree()
	{
		return *m_pSceneOcTree;
	}

	void  SceneGraph::_traverseNode(Node<SceneNode>& begin, SceneNodeProcess func, bool bResursive)
	{
		auto currentCallback = m_pSceneNodeTraverseVisitor->GetCurrentTraverseCallback();
		auto eCurrentTraverseMode = m_pSceneNodeTraverseVisitor->GetTraverseMode();

		m_pSceneNodeTraverseVisitor->SetTraverseCallback(func);
		m_pSceneNodeTraverseVisitor->SetTraverseMode(bResursive ? E_TRAVERSE_MODE::ALL : E_TRAVERSE_MODE::ONLY);
		m_pSceneNodeTraverseVisitor->Apply(begin);

		m_pSceneNodeTraverseVisitor->SetTraverseCallback(currentCallback);
		m_pSceneNodeTraverseVisitor->SetTraverseMode(eCurrentTraverseMode);
	}

	bool  SceneGraph::_getAllSceneNode(LPtr<Node<SceneNode>> pBeginNode, std::vector<Node<SceneNode>*>& outResult)
	{
		outResult.clear();
		SceneNodeProcess _traverseFunc = [&outResult](Node<SceneNode>& rhs)
		{
			outResult.push_back(&rhs);
		};

		_traverseNode(*pBeginNode, _traverseFunc, true);
		return true;
	}

	bool  SceneGraph::_updateNeedAddNode()
	{
		for (auto& node : m_pNeedAddNodeVec)
		{
			m_pRoot->AddChild(node);
			EXIT_IF_FALSE(AddDrawableNodeToSceneOcTree(node));
			EXIT_IF_FALSE(m_pSceneOcTree->AddDrawableNodeToGLPass(m_pSceneRenderPass, node));
		}

		m_pNeedAddNodeVec.clear();
		return true;
	}
}