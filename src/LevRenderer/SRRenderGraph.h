#pragma once

#include <vector>
#include "SSRenderPass.h"

namespace Leviathan
{
	namespace Renderer
	{
		class SSRenderTree;
		
		class SRRenderGraph
		{
		public:
			SRRenderGraph() = default;

			bool InitRenderGraph(const SSRenderTree& render_tree);
			bool Execute();
			
		private:
			std::vector<SSRenderPass> m_render_passes;
		};

		inline bool SRRenderGraph::InitRenderGraph(const SSRenderTree& render_tree)
		{
			m_render_passes.clear();
			
		}

		inline bool SRRenderGraph::Execute()
		{
			
		}
	}
}