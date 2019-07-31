#include "OpenGLRenderTree.h"
#include <utility>
#include "OpenGLRenderEntry.h"
#include "OpenGLPass.h"
#include "NodeVisitor.h"
#include "OpenGLRenderStateManager.h"
#include "OpenGLUniformManager.h"

namespace Leviathan
{
	namespace Renderer
	{
		OpenGLRenderTree::OpenGLRenderTree(LPtr<OpenGLRenderStateManager> render_state_manager)
			: m_root(nullptr)
			, m_render_state_manager(std::move(render_state_manager))
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

		OpenGLRenderNodeObject::OpenGLRenderNodeObject(LPtr<OpenGLRenderEntry> object)
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

		void OpenGLRenderNodeObject::ApplyRenderState(OpenGLRenderStateManager& render_state_manager)
		{
			auto& render_states = m_object->GetRenderState();
			for (auto& state : render_states)
			{
				render_state_manager.ApplyRenderState(state);
			}
		}

		void OpenGLRenderNodeObject::ApplyUniform(OpenGLUniformManager& uniform_manager)
		{
			auto& uniforms = m_object->GetUniforms();
			for (auto& uniform : uniforms)
			{
				uniform_manager.ApplyUniform(uniform);
			}
		}

		void OpenGLRenderNodeObject::Render(GLuint shader_program)
		{
			m_object->Render(shader_program);
		}
	}
}


