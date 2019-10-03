#pragma once
#include "OpenGLRenderEntry.h"
#include "IOpenGLCommand.h"
#include "OpenGLRenderBackend.h"

namespace Leviathan
{
	namespace Renderer
	{
		class OpenGLRenderEntryManager
		{
		public:
			OpenGLRenderEntryManager(OpenGLRenderBackend& render_backend);

			bool CreateRenderEntry(const Scene::LevSceneObject& scene_object, LSPtr<OpenGLRenderEntry>& out);
			bool CreateEmptyRenderEntry(const Scene::LevSceneObject& scene_object, LSPtr<OpenGLRenderEntry>& out);

			bool SetParent(const Scene::LevSceneObject& scene_object, const Scene::LevSceneObject& parent_object);
			bool GetParentID(unsigned id, unsigned& out);
			bool GetRenderEntry(unsigned id, LSPtr<OpenGLRenderEntry>& out);

			template<typename LAMBDA_TYPE>
			bool PushRenderCommand(LAMBDA_TYPE command, OpenGLCommandType type);

			bool FlushRenderCommand();

		private:
			bool _checkEntryExist(unsigned id);

			OpenGLRenderBackend& m_render_backend;

			std::map<unsigned, LSPtr<OpenGLRenderEntry>> m_render_entries;
			std::map<unsigned, unsigned> m_parent_mapping;
		};

		template <typename LAMBDA_TYPE>
		bool OpenGLRenderEntryManager::PushRenderCommand(LAMBDA_TYPE command, OpenGLCommandType type)
		{
			m_render_backend.PushRenderCommand(command, type);
			return true;
		}
	}
}


