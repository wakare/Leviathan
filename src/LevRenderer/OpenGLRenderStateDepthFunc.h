#pragma once

#include "OpenGLRenderState.h"
#include "LevRenderStateDepthFunc.h"
#include "GL/glew.h"

namespace Leviathan
{
	namespace Renderer
	{
		class OpenGLRenderStateDepthFunc : public OpenGLRenderState
		{
		public:
			OpenGLRenderStateDepthFunc(const Scene::LevRenderStateDepthFunc& depth_func);

			virtual void ApplyState();
			virtual void UnApplyState();

		private:
			GLint m_depth_func_value;
			GLint m_last_enum_value;
			GLboolean m_last_enable_depth_test;
		};
	}
}