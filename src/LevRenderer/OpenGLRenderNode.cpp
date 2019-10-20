#include "OpenGLRenderNode.h"

namespace Leviathan
{
	namespace Renderer
	{
		OpenGLRenderNode::OpenGLRenderNode(LSPtr<OpenGLRenderNodeObject> object)
			: Node<OpenGLRenderNodeObject>(object)
		{

		}

		bool OpenGLRenderNode::DelRenderNode(LSPtr<OpenGLRenderNode> render_node, bool recursive)
		{
			if (m_node_data->GetID() == render_node->GetNodeData()->GetID())
			{
				throw "EXCEPTION";
			}

			auto it = GetChildren().begin();
			while (it != GetChildren().end())
			{
				if ((*it)->GetNodeData()->GetID() == render_node->GetNodeData()->GetID())
				{
					GetChildren().erase(it);
					return true;
				}

				++it;
			}

			if (recursive)
			{
				for (auto& child : GetChildren())
				{
					const bool succeed = DelRenderNode(render_node, true);
					if (succeed)
					{
						return true;
					}
				}
			}

			return false;
		}

		void OpenGLRenderNode::Accept(NodeVisitor<OpenGLRenderNodeObject>& nodeVisitor)
		{
			nodeVisitor.Apply(*this);
		}
	}
}
