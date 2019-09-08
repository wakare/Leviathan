#include "OpenGLRenderNode.h"

namespace Leviathan
{
	namespace Renderer
	{
		OpenGLRenderNode::OpenGLRenderNode(LSPtr<OpenGLRenderNodeObject> object)
			: Node<OpenGLRenderNodeObject>(object)
		{

		}

		void OpenGLRenderNode::Accept(NodeVisitor<OpenGLRenderNodeObject>& nodeVisitor)
		{
			nodeVisitor.Apply(*this);
		}
	}
}
