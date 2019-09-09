#pragma once
#include "OpenGLRenderEntry.h"

namespace Leviathan {
	namespace Scene {
		class LevSceneObject;
	}
}

namespace Leviathan
{
	namespace Renderer
	{
		class OpenGLRenderEntryManager
		{
		public:
			OpenGLRenderEntryManager();

			bool CreateRenderEntry(const Scene::LevSceneObject& scene_object, LSPtr<OpenGLRenderEntry>& out);
			bool CreateEmptyRenderEntry(const Scene::LevSceneObject& scene_object, LSPtr<OpenGLRenderEntry>& out);

			bool SetParent(const Scene::LevSceneObject& scene_object, const Scene::LevSceneObject& parent_object);
			bool GetParentID(unsigned id, unsigned& out);
			bool GetRenderEntry(unsigned id, LSPtr<OpenGLRenderEntry>& out);

		private:
			bool _checkEntryExist(unsigned id);

			std::map<unsigned, LSPtr<OpenGLRenderEntry>> m_render_entries;
			std::map<unsigned, unsigned> m_parent_mapping;
		};
	}
}


