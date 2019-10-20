#pragma once
#include "OpenGLRenderNodeObject.h"
#include "Node.h"
#include "NodeVisitor.h"

namespace Leviathan
{
	namespace Renderer
	{
		class OpenGLRenderNode : public Node<OpenGLRenderNodeObject>
		{
		public:
			OpenGLRenderNode(LSPtr<OpenGLRenderNodeObject> object);

			bool DelRenderNode(LSPtr<OpenGLRenderNode> render_node, bool recursive = true);
			void Accept(NodeVisitor<OpenGLRenderNodeObject>& nodeVisitor) override;
		};

	}
}

