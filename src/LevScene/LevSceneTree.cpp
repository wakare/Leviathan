#include "LevSceneTree.h"
#include "LevSceneNode.h"
#include "LevSceneObject.h"
#include "LevResetObjModifiedVisitor.h"
#include "Node.h"

namespace Leviathan
{
	namespace Scene
	{
		LevSceneTree::LevSceneTree()
			: m_resetor(new LevResetObjModifiedVisitor)
			, m_root(nullptr)
		{
			// Init root node
			LPtr<LevSceneObject> rootObj = new LevSceneObject(ELSOT_ROOT);
			m_root.Reset(new LevSceneNode(rootObj));
		}

		bool LevSceneTree::AddNodeToRoot(LPtr<LevSceneNode> pNode, LPtr<LevSceneNode> pParentNode)
		{
			EXIT_IF_FALSE(m_root && pNode);

			auto _pNode = TryCast<LevSceneNode, Node<LevSceneObject>>(pNode);
			EXIT_IF_FALSE(_pNode);

			if (pParentNode)
			{
				pParentNode->AddChild(_pNode);
			}
			else
			{
				m_root->AddChild(_pNode);
			}
			
			pNode->SetModified();
			return true;
		}

		bool LevSceneTree::ResetObjModifiedState()
		{
			m_root->Accept(*m_resetor);
			return true;
		}

		LevSceneNode & LevSceneTree::GetRoot()
		{
			return *m_root;
		}

		const LevSceneNode & LevSceneTree::GetRoot() const
		{
			return *m_root;
		}
	}
}