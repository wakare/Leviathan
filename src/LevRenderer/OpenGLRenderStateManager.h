#pragma once

#include <vector>
#include "LPtr.h"

namespace Leviathan
{
	namespace Renderer
	{
		class OpenGLRenderState;

		class OpenGLRenderStateManager
		{
		public:
			OpenGLRenderStateManager();
			void AddRenderState(LPtr<OpenGLRenderState> redner_state);
			void ApplyAllRenderState();
			void UnApplyAllRenderState();

		private:
			std::vector<LPtr<OpenGLRenderState>> m_render_states;
		};
	}
}