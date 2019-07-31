#pragma once

#include "LPtr.h"
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
			void ApplyRenderState(LPtr<IOpenGLRenderState> render_state);

		private:
			std::map<OpenGLRenderStateType, LPtr<IOpenGLRenderState>> m_current_render_state;
		};
	}
}
