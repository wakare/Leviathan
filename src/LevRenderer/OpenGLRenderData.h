#pragma once

#include <vector>
#include "LPtr.h"

namespace Leviathan
{
	class IMesh;

	namespace Scene
	{
		class LevSceneData;
		class LevMeshObject;
		class LevCamera;
	}

	namespace Renderer
	{
		class OpenGLPass;
		class OpenGLObject;
		
		class OpenGLRenderData
		{
		public:
			OpenGLRenderData();
			
			void Render();
			void UpdateInputData(const Scene::LevSceneData& sceneData);

			bool ConvertMeshToGLObject(const Scene::LevMeshObject& mesh, std::vector<LPtr<OpenGLObject>>& out);
		private:

			bool _convertTriangleMeshToGLObject(LPtr<IMesh> pMesh, LPtr<OpenGLObject>& out);

			void _createDefaultPass(const Scene::LevCamera* pCamera);
			void _registerToPass(LPtr<OpenGLObject> pObject);
			
			std::vector<LPtr<OpenGLPass>> m_passes;
		};
	}
}