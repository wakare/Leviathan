#pragma once

#include "Node.h"
#include <GL/glew.h>
#include <map>

namespace Leviathan
{
	namespace Renderer
	{
		class OpenGLRenderEntry;
		class OpenGLShaderProgram;
		class OpenGLRenderStateManager;
		class OpenGLUniformManager;
		class OpenGLFrameBufferObject;
		class OpenGLRenderNode;

		/*
			One OpenGLPass mapping one OpenGLRenderTree		
		*/
		class OpenGLRenderTree
		{
		public:
			OpenGLRenderTree(LSPtr<OpenGLRenderStateManager> render_state_manager);
			bool AddNodeToRoot(LSPtr<OpenGLRenderNode> node);
			bool ReplaceNode(LSPtr<OpenGLRenderNode> node);
			bool RemoveNode(unsigned handle);

			OpenGLRenderNode& GetRoot();

		private:
			LSPtr<OpenGLRenderNode> m_root;
			LSPtr<OpenGLRenderStateManager> m_render_state_manager;

			std::map<unsigned, LSPtr<OpenGLRenderNode>> m_nodes;
		};
	}
}
