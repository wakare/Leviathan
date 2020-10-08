#include "IRenderNode.h"

namespace Leviathan
{
	namespace Renderer
	{
		// Global node handle
		IRenderNodeHandle GenerateNodeHandle()
		{
			static IRenderNodeHandle _internal_handle = 0;
			return _internal_handle++;
		}

		IRenderNode::IRenderNode(LSPtr<IRenderNodeData> render_node_data, IRenderNodeHandle parent_node_handle)
			: Node<IRenderNodeData>(render_node_data)
			, m_node_handle(GenerateNodeHandle())
			, m_parent_node_handle(parent_node_handle)
		{
		}

		IRenderNodeHandle IRenderNode::GetID() const
		{
			return m_node_handle;
		}

		IRenderNodeHandle IRenderNode::GetParentNodeID() const
		{
			return m_parent_node_handle;
		}

		bool IRenderNode::DelChildRenderNode(LSPtr<IRenderNode> delete_node)
		{
			DelChild(delete_node.To<Node<IRenderNodeData>>());
			return true;
		}
	}
}
