#include "OpenGLResourceManager.h"
#include "OpenGLRenderTree.h"
#include "LevRAttrShaderProgram.h"
#include "OpenGLPass.h"
#include "OpenGLShaderProgram.h"
#include "OpenGLRenderStateManager.h"
#include "OpenGLRenderNodeObject.h"
#include "OpenGLRenderNode.h"
#include "OpenGLObjectManager.h"

namespace Leviathan
{
	namespace Renderer
	{
		OpenGLResourceManager::OpenGLResourceManager()
			: m_render_state_manager(new OpenGLRenderStateManager)
			, m_object_manager(new OpenGLObjectManager)
		{

		}

		Leviathan::Renderer::RenderTreeID OpenGLResourceManager::GetOrCreateRenderTree(const Scene::LevRAttrShaderProgram& shader_program)
		{
			auto it = m_render_trees.find(shader_program.GetID());

			if (it == m_render_trees.end())
			{
				// Create
				m_render_trees[shader_program.GetID()] = new OpenGLRenderTree(m_render_state_manager);

				LPtr<OpenGLShaderProgram> opengl_shader_program = new OpenGLShaderProgram(shader_program);
				m_render_pass[shader_program.GetID()] = new OpenGLPass(opengl_shader_program, *m_render_state_manager);
			}

			return shader_program.GetID();
		}

		bool OpenGLResourceManager::AddGLObjectToRenderTree(RenderTreeID handle, LPtr<OpenGLRenderEntry> pObject)
		{
			auto it = m_render_trees.find(handle);

			if (it == m_render_trees.end())
			{
				return false;
			}

			LPtr<OpenGLRenderNode> node = new OpenGLRenderNode(new OpenGLRenderNodeObject(pObject));
			it->second->AddNodeToRoot(node);

			return true;
		}

		bool OpenGLResourceManager::ReplaceGLObjectFromRenderTree(RenderTreeID handle, LPtr<OpenGLRenderEntry> pObject)
		{
			auto it = m_render_trees.find(handle);

			if (it == m_render_trees.end())
			{
				return false;
			}

			LPtr<OpenGLRenderNode> node = new OpenGLRenderNode(new OpenGLRenderNodeObject(pObject));
			it->second->ReplaceNode(node);

			return true;
		}

		bool OpenGLResourceManager::RemoveRenderTree(RenderTreeID handle, unsigned object_id)
		{
			auto it = m_render_trees.find(handle);

			if (it == m_render_trees.end())
			{
				return false;
			}

			it->second->RemoveNode(object_id);

			return true;
		}

		OpenGLObjectManager& OpenGLResourceManager::GetObjectManager()
		{
			return *m_object_manager;
		}

		bool OpenGLResourceManager::Render()
{
			for (auto& render_tree : m_render_trees)
			{
				auto& pass = m_render_pass[render_tree.first];
				pass->Render(*render_tree.second);
			}

			return true;
		}
	}
}
