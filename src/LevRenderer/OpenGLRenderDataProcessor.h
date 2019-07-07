#pragma once

#include <vector>
#include <map>
#include "LPtr.h"

namespace Leviathan
{
	class IMesh;

	namespace Scene
	{
		class LevLight;
		class LevCamera;
		class LevSceneData;
		class LevMeshObject;
		class LevSceneRenderAttribute;
		class LevSceneTreeSearchVisitor;
		class LevSceneTreeTraverseVisitor;
	}

	namespace Renderer
	{
		class OpenGLPass;
		class OpenGLLight;
		class OpenGLObject;
		class OpenGLObject2;
		class OpenGLResourceManager;

		class OpenGLRenderDataProcessor
		{
		public:
			OpenGLRenderDataProcessor();
			
			void UpdateInputData(const Scene::LevSceneData& sceneData);
			
			OpenGLResourceManager& GetResourceManager();
			const OpenGLResourceManager& GetResourceManager() const;
			
		private:
			bool _applyRenderAttribute(LPtr<OpenGLObject2> objects, const Scene::LevSceneRenderAttribute& render_attribute);

			int m_current_render_tree_id;
			LPtr<OpenGLResourceManager> m_resource_manager;
			LPtr<Scene::LevSceneTreeSearchVisitor> m_searchVisitor;
			LPtr<Scene::LevSceneTreeTraverseVisitor> m_traverseVisitor;
		};
	}
}