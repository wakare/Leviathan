#include "OpenGLRenderEntryManager.h"
#include "OpenGLEmptyRenderEntry.h"
#include "LevSceneObject.h"

namespace Leviathan
{
	namespace Renderer
	{
		OpenGLRenderEntryManager::OpenGLRenderEntryManager()
		= default;

		bool OpenGLRenderEntryManager::CreateRenderEntry(const Scene::LevSceneObject& scene_object, LSPtr<OpenGLRenderEntry>& out)
		{
			if (_checkEntryExist(scene_object.GetID()))
			{
				return false;
			}

			out.Reset(new OpenGLRenderEntry(*this, scene_object));
			return true;
		}

		bool OpenGLRenderEntryManager::CreateEmptyRenderEntry(const Scene::LevSceneObject& scene_object, LSPtr<OpenGLRenderEntry>& out)
		{
			if (_checkEntryExist(scene_object.GetID()))
			{
				return false;
			}

			out.Reset(new OpenGLEmptyRenderEntry(*this, scene_object.GetID()));
			return true;
		}

		bool OpenGLRenderEntryManager::SetParent(const Scene::LevSceneObject& scene_object,
			const Scene::LevSceneObject& parent_object)
		{
			m_parent_mapping[scene_object.GetID()] = parent_object.GetID();
			return true;
		}

		bool OpenGLRenderEntryManager::GetParentID(unsigned id, unsigned& out)
		{
			auto it = m_parent_mapping.find(id);
			if (it == m_parent_mapping.end())
			{
				return false;
			}

			out = it->second;
			return true;
		}

		bool OpenGLRenderEntryManager::GetRenderEntry(unsigned id, LSPtr<OpenGLRenderEntry>& out)
		{
			auto it = m_render_entries.find(id);
			if (it == m_render_entries.end())
			{
				return false;
			}

			out = it->second;
			return true;
		}

		bool OpenGLRenderEntryManager::_checkEntryExist(unsigned id)
		{
			return m_render_entries.find(id) != m_render_entries.end();
		}
	}
}
