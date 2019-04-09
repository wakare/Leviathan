#pragma once

#include <vector>
#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include "IRenderer.h"
#include "LPtr.h"

namespace Leviathan
{
	namespace Renderer
	{
		class OpenGLPass;

		class OpenGLRenderer : public IRenderer
		{
		public:
			OpenGLRenderer(GLFWwindow* pWindow);
			
			bool AddPass(LPtr<OpenGLPass> GLPass);
			bool DelPass(LPtr<OpenGLPass> GLPass);
			bool Clear();

			bool SetInputData(const Scene::LevSceneData& data);
			void Update();

		private:
			void _renderOneFrame();

			GLFWwindow* m_pWindow;
			std::vector<LPtr<OpenGLPass>> m_GLPasses;
		};
	}
}