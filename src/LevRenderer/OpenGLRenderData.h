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
		class LevLight;
	}

	namespace Renderer
	{
		class OpenGLPass;
		class OpenGLObject;
		class OpenGLLight;

		class OpenGLRenderData
		{
		public:
			OpenGLRenderData();
			
			void Render();
			void UpdateInputData(const Scene::LevSceneData& sceneData);

			bool ConvertMeshToGLObject(const Scene::LevMeshObject& mesh, std::vector<LPtr<OpenGLObject>>& out);
		private:
			bool _updateLight(const Scene::LevLight& light);
			bool _convertTriangleMeshToGLObject(LPtr<IMesh> pMesh, LPtr<OpenGLObject>& out);

			void _createDefaultPass(const Scene::LevCamera* pCamera);
			void _registerToPass(LPtr<OpenGLObject> pObject);
			
			bool _setCurrentPass(LPtr<OpenGLPass> pPass);
			OpenGLPass& _currentPass();

			LPtr<OpenGLPass> m_pCurrentPass;
			std::vector<LPtr<OpenGLPass>> m_passes;
			std::vector<LPtr<OpenGLLight>> m_lights;
		};
	}
}