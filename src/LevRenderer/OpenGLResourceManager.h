#pragma once

#include <map>
#include "LSPtr.h"

namespace Leviathan
{
	namespace Scene
	{
		class LevRAttrShaderProgram;
	}

	namespace Renderer
	{
		class OpenGLRenderEntry;
		class OpenGLPass;
		class OpenGLRenderTree;
		class OpenGLRenderNodeObject;
		class OpenGLRenderStateManager;
		class OpenGLObjectManager;
		class OpenGLRenderEntryManager;
		class OpenGLRenderBackend;

		typedef int RenderTreeID;

		class OpenGLResourceManager
		{
		public:
			OpenGLResourceManager(OpenGLRenderBackend& render_backend);

			RenderTreeID GetOrCreateRenderTree(const Scene::LevRAttrShaderProgram& shader_program);
			bool AddGLObjectToRenderTree(RenderTreeID handle, LSPtr<OpenGLRenderEntry> pObject);
			bool ReplaceGLObjectFromRenderTree(RenderTreeID handle, LSPtr<OpenGLRenderEntry> pObject);
			bool RemoveRenderTree(RenderTreeID handle, unsigned object_id);

			OpenGLObjectManager& GetObjectManager();
			OpenGLRenderEntryManager& GetRenderEntryManager();

			bool Render();

		private:
			OpenGLRenderBackend& m_render_backend;

			LSPtr<OpenGLRenderStateManager> m_render_state_manager;
			LSPtr<OpenGLObjectManager> m_object_manager;
			LSPtr<OpenGLRenderEntryManager> m_render_entry_manager;
			std::map<RenderTreeID, LSPtr<OpenGLPass>> m_render_pass;
			std::map<RenderTreeID, LSPtr<OpenGLRenderTree>> m_render_trees;
		};
	}
}