#include "OpenGLRenderTree.h"
#include "OpenGLObject.h"
#include "OpenGLPass.h"
#include "NodeVisitor.h"
#include "OpenGLEmptyObject.h"

namespace Leviathan
{
	namespace Renderer
	{
		OpenGLRenderTree::OpenGLRenderTree()
			: m_root(nullptr)
		{

		}

		bool OpenGLRenderTree::AddNodeToRoot(LPtr<OpenGLRenderNode> node)
		{
			if (!m_root)
			{
				m_root = node;
			}
			else
			{
				m_root->AddChild(TryCast<OpenGLRenderNode, Node<OpenGLRenderNodeObject>>(node));
				m_nodes[node->GetNodeData()->GetID()] = node;
			}

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
			LEV_ASSERT(m_root);
			return *m_root;
		}

		OpenGLRenderNode::OpenGLRenderNode(LPtr<OpenGLRenderNodeObject> object)
			: Node<OpenGLRenderNodeObject>(object)
		{
			
		}

		void OpenGLRenderNode::Accept(NodeVisitor<OpenGLRenderNodeObject>& nodeVisitor)
		{
			nodeVisitor.Apply(*this);
		}

		OpenGLRenderNodeObject::OpenGLRenderNodeObject(LPtr<OpenGLObject> object)
			: m_object(object)
		{
			LEV_ASSERT(object);
		}

		bool OpenGLRenderNodeObject::Valid() const
		{
			return m_object.Get();
		}

		unsigned OpenGLRenderNodeObject::GetID() const
		{
			return m_object->GetID();
		}

		void OpenGLRenderNodeObject::PreRender(GLuint shader_program)
		{
			m_object->PreRender(shader_program);
		}

		void OpenGLRenderNodeObject::Render(GLuint shader_program)
		{
			m_object->Render(shader_program);
		}

		void OpenGLRenderNodeObject::PostRender(GLuint shader_program)
		{
			m_object->PostRender(shader_program);
		}
	}
}


