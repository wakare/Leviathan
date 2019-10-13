#include "OpenGLRenderTree.h"
#include <utility>
#include "OpenGLRenderEntry.h"
#include "OpenGLPass.h"
#include "OpenGLRenderStateManager.h"
#include "OpenGLRenderNode.h"
#include "OpenGLRenderResourceManager.h"
#include "OpenGLEmptyRenderEntry.h"

namespace Leviathan
{
	namespace Renderer
	{
		OpenGLRenderTree::OpenGLRenderTree(OpenGLRenderResourceManager& resource_manager, LSPtr<OpenGLRenderStateManager> render_state_manager)
			: IOpenGLRenderResource(resource_manager)
			, m_root(nullptr)
			, m_render_state_manager(std::move(render_state_manager))
		{

		}

		bool OpenGLRenderTree::AddNode(LSPtr<OpenGLRenderNode> node)
		{
			if (!m_root)
			{
				m_root = node;
			}
			else
			{
				const auto node_id = node->GetNodeData()->GetID();
				unsigned parent_id = UINT_MAX;
				const auto succeed = m_render_entry_manager.GetParentID(node_id, parent_id);
				LEV_ASSERT(succeed);

				const auto it = m_nodes.find(parent_id);
				LEV_ASSERT(it != m_nodes.end());

				it->second->AddChild(node.To<Node<OpenGLRenderNodeObject>>());
			}

			m_nodes[node->GetNodeData()->GetID()] = node;

			return true;
		}

		bool OpenGLRenderTree::ReplaceNode(LSPtr<OpenGLRenderNode> node)
		{
			auto it = m_nodes.find(node->GetNodeData()->GetID());
			if (it == m_nodes.end())
			{
				return AddNode(node);
			}

			it->second->SetNodeData(node->GetNodeData());
			return true;
		}

		bool OpenGLRenderTree::RemoveNode(unsigned handle)
		{
			const auto it = m_nodes.find(handle);
			if (it == m_nodes.end())
			{
				return false;
			}

			it->second->SetInvalid();
			return true;
		}

		OpenGLRenderNode & OpenGLRenderTree::GetRoot()
		{
			LEV_ASSERT(m_root);
			return *m_root;
		}
	}
}


