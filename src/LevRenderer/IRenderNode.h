#pragma once
#include "IRenderNodeData.h"
#include "Node.h"

namespace Leviathan
{
	namespace Renderer
	{
		typedef uint32_t IRenderNodeHandle;
		static const IRenderNodeHandle IRenderNodeHandle_MAX = UINT32_MAX;
		
		class IRenderNode : public Node<IRenderNodeData>
		{
		public:
			IRenderNode(LSPtr<IRenderNodeData> render_node_data, IRenderNodeHandle parent_node_handle);
			
			IRenderNodeHandle GetID() const;
			IRenderNodeHandle GetParentNodeID() const;

			bool DelChildRenderNode(LSPtr<IRenderNode> delete_node);
			
		private:
			IRenderNodeHandle m_node_handle;
			IRenderNodeHandle m_parent_node_handle;
		};
	}
}
