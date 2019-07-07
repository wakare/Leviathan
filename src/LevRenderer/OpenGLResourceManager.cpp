#include "OpenGLResourceManager.h"
#include "OpenGLRenderTree.h"
#include "LevRAttrShaderProgram.h"
#include "OpenGLPass2.h"
#include "OpenGLShaderProgram.h"

namespace Leviathan
{
	namespace Renderer
	{
		OpenGLResourceManager::OpenGLResourceManager()
		{

		}

		Leviathan::Renderer::RenderTreeID OpenGLResourceManager::GetOrCreateRenderTree(const Scene::LevRAttrShaderProgram& shader_program)
		{
			auto it = m_render_trees.find(shader_program.GetID());

			if (it == m_render_trees.end())
			{
				// Create
				m_render_trees[shader_program.GetID()] = new OpenGLRenderTree;

				LPtr<OpenGLShaderProgram> opengl_shader_program = new OpenGLShaderProgram(shader_program);
				m_render_pass[shader_program.GetID()] = new OpenGLPass2(opengl_shader_program);
			}

			return shader_program.GetID();
		}

		bool OpenGLResourceManager::AddGLObject(RenderTreeID handle, LPtr<OpenGLObject2> pObject)
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

		bool OpenGLResourceManager::ReplaceGLObject(RenderTreeID handle, LPtr<OpenGLObject2> pObject)
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

		bool OpenGLResourceManager::RemoveResource(RenderTreeID handle, unsigned object_id)
		{
			auto it = m_render_trees.find(handle);

			if (it == m_render_trees.end())
			{
				return false;
			}

			it->second->RemoveNode(object_id);

			return true;
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
