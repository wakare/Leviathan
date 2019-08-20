#include "OpenGLRenderTree.h"
#include <utility>
#include "OpenGLRenderEntry.h"
#include "OpenGLPass.h"
#include "OpenGLRenderStateManager.h"
#include "OpenGLRenderNode.h"

namespace Leviathan
{
	namespace Renderer
	{
		OpenGLRenderTree::OpenGLRenderTree(LPtr<OpenGLRenderStateManager> render_state_manager)
			: m_root(nullptr)
			, m_render_state_manager(std::move(render_state_manager))
		{

		}

		bool OpenGLRenderTree::AddNodeToRoot(LPtr<OpenGLRenderNode> node)
		{
			if (!m_root)
			{
				m_root = node;
			}
			else
			{
				m_root->AddChild(TryCast<OpenGLRenderNode, Node<OpenGLRenderNodeObject>>(node));
				m_nodes[node->GetNodeData()->GetID()] = node;
			}

			return true;
		}

		bool OpenGLRenderTree::ReplaceNode(LPtr<OpenGLRenderNode> node)
		{
			auto it = m_nodes.find(node->GetNodeData()->GetID());
			if (it == m_nodes.end())
			{
				return AddNodeToRoot(node);
			}

			it->second->SetNodeData(node->GetNodeData());
			return true;
		}

		bool OpenGLRenderTree::RemoveNode(unsigned handle)
		{
			auto it = m_nodes.find(handle);
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


