#include "OpenGLRenderTree.h"
#include "OpenGLObject.h"
#include "OpenGLPass.h"

namespace Leviathan
{
	namespace Renderer
	{
		OpenGLRenderTree::OpenGLRenderTree()
			: m_root(new OpenGLRenderNode(new OpenGLRenderNodeObject(nullptr)))
		{

		}

		bool OpenGLRenderTree::AddNodeToRoot(LPtr<OpenGLRenderNode> node)
		{
			m_root->AddChild(TryCast<OpenGLRenderNode, Node<OpenGLRenderNodeObject>>(node));
			m_nodes[node->GetNodeData()->GetID()] = node;

			return true;
		}

		bool OpenGLRenderTree::ReplaceNode(LPtr<OpenGLRenderNode> node)
		{
			auto it = m_nodes.find(node->GetNodeData()->GetID());
			if (it == m_nodes.end())
			{
				return false;
			}

			it->second->SetNodeData(node->GetNodeData());

			return true;
		}

		bool OpenGLRenderTree::RemoveNode(unsigned handle)
		{
			auto it = m_nodes.find(handle);
			if (it == m_nodes.end())
			{
				return false;
			}

			it->second->SetInvalid();
			return true;
		}

		OpenGLRenderNode & OpenGLRenderTree::GetRoot()
		{
			return *m_root;
		}

		OpenGLRenderNode::OpenGLRenderNode(LPtr<OpenGLRenderNodeObject> object)
			: Node<OpenGLRenderNodeObject>(object)
		{
		}

		OpenGLRenderNodeObject::OpenGLRenderNodeObject(LPtr<OpenGLObject> object)
			: m_object(object)
		{
		}

		bool OpenGLRenderNodeObject::Valid() const
		{
			return m_object.Get();
		}

		unsigned OpenGLRenderNodeObject::GetID() const
{
			return m_object->GetID();
		}

		void OpenGLRenderNodeObject::Render(GLuint shader_program)
		{
			m_object->Render(shader_program);
		}

	}
}


