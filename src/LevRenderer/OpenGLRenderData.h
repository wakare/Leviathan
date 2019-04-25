#pragma once

#include <vector>
#include <map>
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
		class LevSceneTreeTraverseVisitor;
		class LevSceneTreeSearchVisitor;
		class LevSceneRenderAttribute;
	}

	namespace Renderer
	{
		class OpenGLPass;
		class OpenGLObject;
		class OpenGLLight;
		class OpenGLResourceMgr;

		class OpenGLRenderData
		{
		public:
			OpenGLRenderData();
			
			void Render();
			void UpdateInputData(const Scene::LevSceneData& sceneData);

			bool ConvertMeshToGLObject(unsigned id, const Scene::LevMeshObject& mesh, std::vector<LPtr<OpenGLObject>>& out);
		private:
			bool _updateLight(const Scene::LevLight& light);
			bool _updateCamera(const Scene::LevCamera& camera);
			bool _convertTriangleMeshToGLObject(unsigned index, LPtr<IMesh> pMesh, LPtr<OpenGLObject>& out);
			bool _convertPointMeshToGLObject(unsigned id, LPtr<IMesh> pMesh, LPtr<OpenGLObject>& out);

			void _createDefaultPass(const Scene::LevCamera* pCamera);
			void _registerToPass(unsigned index, LPtr<OpenGLObject> pObject);
			void _unregisterFromPass(unsigned index);
			
			bool _setCurrentPass(LPtr<OpenGLPass> pPass);
			bool _applyRenderAttribute(std::vector<LPtr<OpenGLObject>>& objects, const Scene::LevSceneRenderAttribute& render_attribute);
			OpenGLPass& _currentPass();

			LPtr<OpenGLPass> m_pCurrentPass;
			LPtr<OpenGLResourceMgr> m_resourceMgr;
			LPtr<Scene::LevSceneTreeSearchVisitor> m_searchVisitor;
			LPtr<Scene::LevSceneTreeTraverseVisitor> m_traverseVisitor;
			std::vector<LPtr<OpenGLPass>> m_passes;
			std::vector<LPtr<OpenGLLight>> m_lights;

			std::map<unsigned, std::vector<LPtr<OpenGLObject>>> m_registerRenderableObjects;
		};
	}
}