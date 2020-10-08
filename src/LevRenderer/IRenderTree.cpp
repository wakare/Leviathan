#include "IRenderTree.h"

namespace Leviathan
{
	namespace Renderer
	{
		bool IRenderTree::AddNode(LSPtr<IRenderNode> node)
		{
			if (!m_rootNode)
			{
				m_rootNode = node;
			}
			else
			{
				const auto node_id = node->GetID();

				const auto parent_node = node->GetParent().To<IRenderNode>();
				const auto it = m_renderNodeMap.find(parent_node.Get() ? parent_node->GetID() : IRenderNodeHandle_MAX);
				
				LEV_ASSERT(it != m_renderNodeMap.end());
				it->second->AddChild(node.To<Node<IRenderNodeData>>());
			}

			m_renderNodeMap[node->GetID()] = node;

			return true;
		}

		bool IRenderTree::FindAndReplaceNode(LSPtr<IRenderNode> node)
		{
			auto it = m_renderNodeMap.find(node->GetID());
			if (it == m_renderNodeMap.end())
			{
				return AddNode(node);
			}

			it->second->SetNodeData(node->GetNodeData());
			return true;
		}

		bool IRenderTree::RemoveNode(IRenderNodeHandle handle)
		{
			const auto it = m_renderNodeMap.find(handle);
			if (it == m_renderNodeMap.end())
			{
				return false;
			}

			const bool deleted = m_rootNode->DelChildRenderNode(it->second);
			LEV_ASSERT(deleted);

			m_renderNodeMap.erase(it);
			return true;
		}

		LSPtr<IRenderNode> IRenderTree::GetRootNode() const
		{
			return m_rootNode;
		}
	}
}
