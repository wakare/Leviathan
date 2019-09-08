#pragma once

#include <map>
#include "LSPtr.h"
#include "Singleton.h"

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

		typedef int RenderTreeID;

		class OpenGLResourceManager : public Singleton<OpenGLResourceManager>
		{
		public:
			DECLARE_SELF_TO_SINGLETON(OpenGLResourceManager)

			RenderTreeID GetOrCreateRenderTree(const Scene::LevRAttrShaderProgram& shader_program);
			bool AddGLObjectToRenderTree(RenderTreeID handle, LSPtr<OpenGLRenderEntry> pObject);
			bool ReplaceGLObjectFromRenderTree(RenderTreeID handle, LSPtr<OpenGLRenderEntry> pObject);
			bool RemoveRenderTree(RenderTreeID handle, unsigned object_id);

			OpenGLObjectManager& GetObjectManager();

			bool Render();

		private:
			OpenGLResourceManager();

			LSPtr<OpenGLRenderStateManager> m_render_state_manager;
			LSPtr<OpenGLObjectManager> m_object_manager;
			std::map<RenderTreeID, LSPtr<OpenGLPass>> m_render_pass;
			std::map<RenderTreeID, LSPtr<OpenGLRenderTree>> m_render_trees;
		};
	}
}