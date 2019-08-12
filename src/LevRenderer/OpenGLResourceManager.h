#pragma once

#include <map>
#include "LPtr.h"

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

		typedef int RenderTreeID;
		class OpenGLResourceManager
		{
		public:
			OpenGLResourceManager();
			RenderTreeID GetOrCreateRenderTree(const Scene::LevRAttrShaderProgram& shader_program);
			bool AddGLObjectToRenderTree(RenderTreeID handle, LPtr<OpenGLRenderEntry> pObject);
			bool ReplaceGLObjectFromRenderTree(RenderTreeID handle, LPtr<OpenGLRenderEntry> pObject);
			bool RemoveResource(RenderTreeID handle, unsigned object_id);

			bool Render();

		private:
			LPtr<OpenGLRenderStateManager> m_render_state_manager;
			std::map<RenderTreeID, LPtr<OpenGLPass>> m_render_pass;
			std::map<RenderTreeID, LPtr<OpenGLRenderTree>> m_render_trees;
		};
	}
}