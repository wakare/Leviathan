#pragma once

#include "LPtr.h"

namespace Leviathan
{
	namespace Renderer
	{
		enum OpenGLRenderStateType
		{
			EOGLRST_POINT_SIZE,
			EOGLRST_DEPTH_FUNC,
		};

		class OpenGLRStatePointSize;
		class OpenGLRStateDepthFunc;

		class IOpenGLRenderState
		{
		public:
			/*
				Apply should be called before render actually object,
				after rendering, UnApply can be called to resume render context.
			*/
			virtual ~IOpenGLRenderState() = default;
			virtual OpenGLRenderStateType GetRenderStateType() const = 0;

			virtual OpenGLRStatePointSize* ToPointSize() { return nullptr; }
			virtual OpenGLRStateDepthFunc* ToDepthFunc() { return nullptr; }

			virtual void Apply() = 0;
			virtual void UnApply() = 0;

			void SetLastRenderState(LPtr<IOpenGLRenderState> last_render_state);

		protected:
			LPtr<IOpenGLRenderState> m_last_render_state;
		};

		inline void IOpenGLRenderState::SetLastRenderState(LPtr<IOpenGLRenderState> last_render_state)
		{
			m_last_render_state = last_render_state;
		}
	}
}