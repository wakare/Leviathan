#pragma once

#include <map>

#include "IRenderNode.h"
#include "LSPtr.h"

namespace Leviathan
{
	namespace Renderer
	{
		class IRenderTree
		{
		public:
			virtual ~IRenderTree() = default;

			bool AddNode(LSPtr<IRenderNode> Node);
			bool FindAndReplaceNode(LSPtr<IRenderNode> Node);
			bool RemoveNode(IRenderNodeHandle Handle);

			LSPtr<IRenderNode> GetRootNode() const;
			
		private:
			LSPtr<IRenderNode> m_rootNode;
			std::map<IRenderNodeHandle, LSPtr<IRenderNode>> m_renderNodeMap;
		};
	}
}
