#pragma once

#include "Node.h"
#include <GL/glew.h>
#include <map>
#include "IOpenGLRenderResource.h"

namespace Leviathan
{
	namespace Renderer
	{
		class OpenGLRenderEntry;
		class OpenGLShaderProgram;
		class OpenGLRenderStateManager;
		class OpenGLProgramUniformManager;
		class OpenGLFrameBufferObject;
		class OpenGLRenderNode;
		class OpenGLRenderResourceManager;
		/*
			One OpenGLPass mapping one OpenGLRenderTree		
		*/
		class OpenGLRenderTree : public IOpenGLRenderResource
		{
		public:
			OpenGLRenderTree(OpenGLRenderResourceManager& resource_manager);
			bool AddNode(LSPtr<OpenGLRenderNode> node);
			bool ReplaceNode(LSPtr<OpenGLRenderNode> node);
			bool RemoveNode(unsigned handle);

			OpenGLRenderNode& GetRoot();

		private:
			LSPtr<OpenGLRenderNode> m_root;

			std::map<unsigned, LSPtr<OpenGLRenderNode>> m_nodes;
		};
	}
}
