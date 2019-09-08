#pragma once

#include "LSPtr.h"
#include <map>
#include "IOpenGLRenderState.h"

namespace Leviathan
{
	namespace Renderer
	{
		class IOpenGLRenderState;

		class OpenGLRenderStateManager
		{
		public:
			OpenGLRenderStateManager();
			void ApplyRenderState(LSPtr<IOpenGLRenderState> render_state);

		private:
			std::map<OpenGLRenderStateType, LSPtr<IOpenGLRenderState>> m_current_render_state;
		};
	}
}
