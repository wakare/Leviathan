#pragma once

#include "IOpenGLRenderState.h"
#include "LevRenderStateDepthFunc.h"
#include "GL/glew.h"

namespace Leviathan
{
	namespace Renderer
	{
		class OpenGLRStateDepthFunc : public IOpenGLRenderState
		{
		public:
			OpenGLRStateDepthFunc(const Scene::LevRenderStateDepthFunc& depth_func);

			OpenGLRStateDepthFunc* ToDepthFunc() override;

			OpenGLRenderStateType GetRenderStateType() const override;

			void Apply() override;
			void UnApply() override;

		private:
			GLuint m_depth_func_value;
		};
	}
}