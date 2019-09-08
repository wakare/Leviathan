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
			virtual void Accept(NodeVisitor<OpenGLRenderNodeObject>& nodeVisitor);
		};

	}
}

