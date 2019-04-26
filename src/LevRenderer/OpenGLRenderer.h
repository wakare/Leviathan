#pragma once

#include <vector>
#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include "IRenderer.h"
#include "LPtr.h"

namespace Leviathan
{
	class LevOpenGLWindow;

	namespace Renderer
	{
		class OpenGLPass;
		class OpenGLRenderData;

		class OpenGLRenderer : public IRenderer
		{
		public:
			OpenGLRenderer(LevOpenGLWindow& pWindow);
			
			bool Clear();

			bool SetInputData(const Scene::LevSceneData& data);
			void Update();

		private:
			void _renderOneFrame();

			LevOpenGLWindow& m_window;
			LPtr<OpenGLRenderData> m_pRenderData;
		};
	}
}