#include "OpenGLRenderResourceManager.h"
#include "OpenGLEmptyRenderEntry.h"
#include "LevSceneObject.h"

namespace Leviathan
{
	namespace Renderer
	{
		OpenGLRenderResourceManager::OpenGLRenderResourceManager(OpenGLResourceManager& resource_manager)
			: m_resource_manager(resource_manager)
		{
		}

		bool OpenGLRenderResourceManager::CreateRenderEntry(const Scene::LevSceneObject& scene_object, LSPtr<OpenGLRenderEntry>& out)
		{
			if (_checkEntryExist(scene_object.GetID()))
			{
				return false;
			}

			out.Reset(new OpenGLRenderEntry(*this, scene_object));
			m_render_entries[scene_object.GetID()] = out;
			return true;
		}

		bool OpenGLRenderResourceManager::CreateEmptyRenderEntry(const Scene::LevSceneObject& scene_object, LSPtr<OpenGLRenderEntry>& out)
		{
			if (_checkEntryExist(scene_object.GetID()))
			{
				return false;
			}

			out.Reset(new OpenGLEmptyRenderEntry(*this, scene_object.GetID()));
			m_render_entries[scene_object.GetID()] = out;
			return true;
		}

		bool OpenGLRenderResourceManager::UpdateRenderEntry(const Scene::LevSceneObject& scene_object,
			LSPtr<OpenGLRenderEntry>& out)
		{
			if (!_checkEntryExist(scene_object.GetID()))
			{
				return false;
			}

			out.Reset(new OpenGLRenderEntry(*this, scene_object));
			m_render_entries[scene_object.GetID()] = out;
			return true;
		}

		bool OpenGLRenderResourceManager::UpdateEmptyRenderEntry(const Scene::LevSceneObject& scene_object,
			LSPtr<OpenGLRenderEntry>& out)
		{
			if (!_checkEntryExist(scene_object.GetID()))
			{
				return false;
			}

			out.Reset(new OpenGLEmptyRenderEntry(*this, scene_object.GetID()));
			m_render_entries[scene_object.GetID()] = out;
			return true;
		}

		bool OpenGLRenderResourceManager::RemoveRenderEntry(unsigned id)
		{
			if (!_checkEntryExist(id))
			{
				return false;
			}

			m_parent_mapping.erase(m_parent_mapping.find(id));
			m_render_entries.erase(m_render_entries.find(id));
			
			return true;
		}

		bool OpenGLRenderResourceManager::SetParent(const Scene::LevSceneObject& scene_object,
			const Scene::LevSceneObject& parent_object)
		{
			m_parent_mapping[scene_object.GetID()] = parent_object.GetID();
			return true;
		}

		bool OpenGLRenderResourceManager::GetParentID(unsigned id, unsigned& out)
		{
			auto it = m_parent_mapping.find(id);
			if (it == m_parent_mapping.end())
			{
				return false;
			}

			out = it->second;
			return true;
		}

		bool OpenGLRenderResourceManager::GetRenderEntry(unsigned id, LSPtr<OpenGLRenderEntry>& out)
		{
			auto it = m_render_entries.find(id);
			if (it == m_render_entries.end())
			{
				return false;
			}

			out = it->second;
			return true;
		}

		OpenGLResourceManager& OpenGLRenderResourceManager::GetResourceManager()
		{
			return m_resource_manager;
		}

		bool OpenGLRenderResourceManager::_checkEntryExist(unsigned id)
		{
			return m_render_entries.find(id) != m_render_entries.end();
		}
	}
}
