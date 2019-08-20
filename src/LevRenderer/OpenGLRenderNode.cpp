#include "OpenGLRenderNode.h"

namespace Leviathan
{
	namespace Renderer
	{
		OpenGLRenderNode::OpenGLRenderNode(LPtr<OpenGLRenderNodeObject> object)
			: Node<OpenGLRenderNodeObject>(object)
		{

		}

		void OpenGLRenderNode::Accept(NodeVisitor<OpenGLRenderNodeObject>& nodeVisitor)
		{
			nodeVisitor.Apply(*this);
		}
	}
}
