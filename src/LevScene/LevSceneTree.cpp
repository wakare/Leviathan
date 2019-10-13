#include "Node.h"
#include "LevSceneTree.h"
#include "LevSceneNode.h"
#include "LevSceneObject.h"
#include "LevResetObjModifiedVisitor.h"
#include "LevSetObjectModifiedVisitor.h"
#include "LevStateUpdaterVisitor.h"
#include "LevCalculateWorldCoordVisitor.h"
#include "LevTimerTickVisitor.h"
#include "LevUserUpdateVisitor.h"

namespace Leviathan
{
	namespace Scene
	{
		LevSceneTree::LevSceneTree()
			: m_modified_resetor(new LevResetObjModifiedVisitor)
			, m_state_updater(new LevStateUpdaterVisitor)
			, m_modified_setor(new LevSetObjModifiedVisitor)
			, m_worldCoord_updater(new LevCalculateWorldCoordVisitor)
			, m_time_ticker(new LevTimerTickVisitor)
			, m_user_updater(new LevUserUpdateVisitor)
			, m_root(nullptr)
		{
			// Init root node
			LSPtr<LevSceneObject> rootObj = new LevSceneObject(ELSOT_ROOT);
			m_root.Reset(new LevSceneNode(rootObj));

			// Set state update callback
			auto _state_updater = [](LevSceneObject& object)
			{
				// Update node state:
					// 0. added state --> unmodified state
					// 1. unmodified state --> the same
					// 2. modified state --> unmodified state
					// 3. disable state --> the same [state must be changed by external request --> unmodified]
					// 4. deleted state --> true delete & remove node

				switch (object.GetState())
				{
				case ELSOS_ADDED:
					object.SetState(ELSOS_UNMODIFIED);
					break;

				case ELSOS_UPDATE:
					object.SetState(ELSOS_UNMODIFIED);
					break;
				}

				return true;
			};

			m_state_updater->SetStateUpdateCallback(_state_updater);
		}

		bool LevSceneTree::AddNodeToParent(LSPtr<LevSceneNode> pNode, LSPtr<LevSceneNode> pParentNode /*= nullptr*/)
		{
			EXIT_IF_FALSE(m_root && pNode);

			if (pParentNode)
			{
				pParentNode->AddChild(pNode);
			}
			else
			{
				m_root->AddChild(pNode);
			}
			
			pNode->SetModified();
			return true;
		}

		bool LevSceneTree::ResetObjUnModified()
		{
			m_root->Accept(*m_modified_resetor);
			return true;
		}

		bool LevSceneTree::SetObjModified()
		{
			m_root->Accept(*m_modified_setor);
			return true;
		}

		bool LevSceneTree::UpdateWorldCoord()
		{
			m_root->Accept(*m_worldCoord_updater);
			return true;
		}

		bool LevSceneTree::UpdateTimer()
		{
			m_time_ticker->Apply(*m_root);
			return true;
		}

		bool LevSceneTree::DoUserUpdataCallback()
		{
			m_user_updater->Apply(*m_root);
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

		void LevSceneTree::UpdateNodeState()
		{
			_checkDeleteNode(*m_root);
			m_state_updater->Apply(*m_root);
		}

		void LevSceneTree::_checkDeleteNode(LevSceneNode& pBeginNode)
		{
			LEV_ASSERT(pBeginNode.GetNodeData()->GetState() != ELSOS_DELETED);

			Node<LevSceneObject>& begin_node = pBeginNode;

			auto it = begin_node.GetChildren().begin();
			while (it != begin_node.GetChildren().end())
			{
				if ((*it)->GetNodeData()->GetState() == ELSOS_DELETED)
				{
					it = begin_node.GetChildren().erase(it);
					continue;
				}

				++it;
			}

			/*
			//Delete children
			std::vector<LSPtr<Node<LevSceneObject>>> deletedChildren;
			for (auto& child : begin_node.GetChildren())
			{
				if (child->GetNodeData()->GetState() == ELSOS_DELETED)
				{
					deletedChildren.push_back(child);
				}
			}

			for (auto& child : deletedChildren)
			{
				begin_node.DelChild(child);
			}*/

			for (auto& child : pBeginNode.GetChildren())
			{
				LevSceneNode* _child = dynamic_cast<LevSceneNode*>(child.Get());
				if (_child)
				{
					_checkDeleteNode(*_child);
				}
			}
		}
	}
}
