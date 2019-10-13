#pragma once

#include <map>
#include "LSPtr.h"
#include "IOpenGLCommand.h"
#include "OpenGLRenderBackend.h"

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
		class OpenGLRenderResourceManager;
		class OpenGLUniformManager;

		typedef int RenderTreeID;

		class OpenGLResourceManager
		{
		public:
			OpenGLResourceManager(OpenGLRenderBackend& render_backend);

			RenderTreeID GetOrCreateRenderTree(const Scene::LevRAttrShaderProgram& shader_program);
			bool AddGLObjectToRenderTree(RenderTreeID handle, LSPtr<OpenGLRenderEntry> pObject);
			bool ReplaceGLObjectFromRenderTree(RenderTreeID handle, LSPtr<OpenGLRenderEntry> pObject);
			bool RemoveGLObjectFromRenderTree(RenderTreeID handle, unsigned object_id);

			OpenGLObjectManager& GetObjectManager();
			OpenGLRenderResourceManager& GetRenderEntryManager();

			bool Render();

			template<typename LAMBDA_TYPE>
			bool PushRenderCommand(LAMBDA_TYPE command, OpenGLCommandType type);

			bool FlushRenderCommand();

		private:
			OpenGLRenderBackend& m_render_backend;

			LSPtr<OpenGLRenderStateManager> m_render_state_manager;
			LSPtr<OpenGLObjectManager> m_object_manager;
			LSPtr<OpenGLUniformManager> m_uniform_manager;
			LSPtr<OpenGLRenderResourceManager> m_render_entry_manager;

			std::map<RenderTreeID, LSPtr<OpenGLPass>> m_render_pass;
			std::map<RenderTreeID, LSPtr<OpenGLRenderTree>> m_render_trees;
		};

		template <typename LAMBDA_TYPE>
		bool OpenGLResourceManager::PushRenderCommand(LAMBDA_TYPE command, OpenGLCommandType type)
		{
			m_render_backend.PushRenderCommand(command, type);
			return true;
		}
	}
}
