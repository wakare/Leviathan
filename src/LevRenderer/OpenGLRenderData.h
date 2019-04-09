#pragma once

#include <vector>
#include "LPtr.h"

namespace Leviathan
{
	namespace Scene
	{
		class LevSceneData;
		class LevMeshObject;
	}

	namespace Renderer
	{
		class OpenGLPass;
		class OpenGL3DObject;

		class OpenGLRenderData
		{
		public:
			OpenGLRenderData();
			void UpdateInputData(const Scene::LevSceneData& sceneData);

			bool ConvertMeshToGLObject(const Scene::LevMeshObject& mesh, LPtr<OpenGL3DObject>& out);

		private:
			std::vector<OpenGLPass> m_passes;
		};
	}
}