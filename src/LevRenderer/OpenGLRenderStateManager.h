#pragma once

#include "LSPtr.h"
#include <map>
#include "IOpenGLRenderState.h"
#include "OpenGLRenderBackend.h"

namespace Leviathan
{
	namespace Renderer
	{
		class IOpenGLRenderState;
		class OpenGLResourceManager;

		class OpenGLRenderStateManager
		{
		public:
			OpenGLRenderStateManager(OpenGLResourceManager& resource_manager);
			void ApplyRenderState(LSPtr<IOpenGLRenderState> render_state);

		private:
			OpenGLResourceManager& m_resource_manager;
			std::map<OpenGLRenderStateType, LSPtr<IOpenGLRenderState>> m_current_render_state;
		}; 
	}
}
