#pragma once

#include "LSPtr.h"

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

			void SetLastRenderState(LSPtr<IOpenGLRenderState> last_render_state);

		protected:
			LSPtr<IOpenGLRenderState> m_last_render_state;
		};

		inline void IOpenGLRenderState::SetLastRenderState(LSPtr<IOpenGLRenderState> last_render_state)
		{
			m_last_render_state = last_render_state;
		}
	}
}