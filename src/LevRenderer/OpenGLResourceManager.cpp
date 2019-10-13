#include "OpenGLResourceManager.h"
#include "OpenGLRenderTree.h"
#include "LevRAttrShaderProgram.h"
#include "OpenGLPass.h"
#include "OpenGLShaderProgram.h"
#include "OpenGLRenderStateManager.h"
#include "OpenGLRenderNodeObject.h"
#include "OpenGLRenderNode.h"
#include "OpenGLObjectManager.h"
#include "OpenGLRenderResourceManager.h"
#include "OpenGLUniformManager.h"
#include "OpenGLProgramUniformManager.h"

namespace Leviathan
{
	namespace Renderer
	{
		OpenGLResourceManager::OpenGLResourceManager(OpenGLRenderBackend& render_backend)
			: m_render_backend(render_backend)
			, m_render_state_manager(new OpenGLRenderStateManager(*this))
			, m_object_manager(new OpenGLObjectManager(*this))
			, m_uniform_manager(new OpenGLUniformManager)
			, m_render_entry_manager(new OpenGLRenderResourceManager(*this))
		{

		}

		Leviathan::Renderer::RenderTreeID OpenGLResourceManager::GetOrCreateRenderTree(const Scene::LevRAttrShaderProgram& shader_program)
		{
			auto it = m_render_trees.find(shader_program.GetID());

			if (it == m_render_trees.end())
			{
				// Create
				m_render_trees[shader_program.GetID()] = new OpenGLRenderTree(*m_render_entry_manager, m_render_state_manager);

				LSPtr<OpenGLShaderProgram> gl_shader_program = new OpenGLShaderProgram(*m_object_manager, shader_program);

				LSPtr<OpenGLProgramUniformManager> program_uniform_manager = nullptr;
				const bool _created = m_uniform_manager->CreateProgramUniformManager(gl_shader_program, program_uniform_manager);
				assert(_created);

				m_render_pass[shader_program.GetID()] = new OpenGLPass(*m_render_entry_manager, gl_shader_program, program_uniform_manager, *m_render_state_manager);
			}

			return shader_program.GetID();
		}

		bool OpenGLResourceManager::AddGLObjectToRenderTree(RenderTreeID handle, LSPtr<OpenGLRenderEntry> pObject)
		{
			auto it = m_render_trees.find(handle);

			if (it == m_render_trees.end())
			{
				return false;
			}

			LSPtr<OpenGLRenderNode> node = new OpenGLRenderNode(new OpenGLRenderNodeObject(pObject));
			it->second->AddNode(node);

			return true;
		}

		bool OpenGLResourceManager::ReplaceGLObjectFromRenderTree(RenderTreeID handle, LSPtr<OpenGLRenderEntry> pObject)
		{
			auto it = m_render_trees.find(handle);

			if (it == m_render_trees.end())
			{
				return false;
			}

			LSPtr<OpenGLRenderNode> node = new OpenGLRenderNode(new OpenGLRenderNodeObject(pObject));
			it->second->ReplaceNode(node);

			return true;
		}

		bool OpenGLResourceManager::RemoveGLObjectFromRenderTree(RenderTreeID handle, unsigned object_id)
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

		OpenGLRenderResourceManager& OpenGLResourceManager::GetRenderEntryManager()
		{
			return *m_render_entry_manager;
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

		bool OpenGLResourceManager::FlushRenderCommand()
		{
			return m_render_backend.FlushRenderCommand();
		}
	}
}
