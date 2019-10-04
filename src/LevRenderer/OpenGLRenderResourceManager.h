#pragma once
#include <map>
#include "OpenGLRenderBackend.h"

namespace Leviathan
{
	namespace Renderer
	{
		class OpenGLResourceManager;
		class OpenGLRenderEntry;
		class OpenGLRenderResourceManager
		{
		public:
			OpenGLRenderResourceManager(OpenGLResourceManager& resource_manager);

			bool CreateRenderEntry(const Scene::LevSceneObject& scene_object, LSPtr<OpenGLRenderEntry>& out);
			bool CreateEmptyRenderEntry(const Scene::LevSceneObject& scene_object, LSPtr<OpenGLRenderEntry>& out);

			bool SetParent(const Scene::LevSceneObject& scene_object, const Scene::LevSceneObject& parent_object);
			bool GetParentID(unsigned id, unsigned& out);
			bool GetRenderEntry(unsigned id, LSPtr<OpenGLRenderEntry>& out);

			OpenGLResourceManager& GetResourceManager();

		private:
			bool _checkEntryExist(unsigned id);

			OpenGLResourceManager& m_resource_manager;

			std::map<unsigned, LSPtr<OpenGLRenderEntry>> m_render_entries;
			std::map<unsigned, unsigned> m_parent_mapping;
		};
	}
}


