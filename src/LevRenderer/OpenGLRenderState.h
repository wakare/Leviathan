#pragma once

namespace Leviathan
{
	namespace Renderer
	{
		class OpenGLRenderState
		{
		public:
			/*
				ApplyState should be called before render actually object,
				after rendering, UnApplyState can be called to resume render context.
			*/
			virtual void ApplyState() = 0;
			virtual void UnApplyState() = 0;
		};
	}
}