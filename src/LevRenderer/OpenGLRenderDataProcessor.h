#pragma once

#include <vector>
#include <map>
#include "LSPtr.h"

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
		class OpenGLRenderEntry;
		class OpenGLRenderEntry;
		class OpenGLResourceManager;
		class OpenGLObjectManager;

		class OpenGLRenderDataProcessor
		{
		public:
			OpenGLRenderDataProcessor();
			
			void UpdateInputData(const Scene::LevSceneData& sceneData);
			
			OpenGLResourceManager& GetResourceManager();
			const OpenGLResourceManager& GetResourceManager() const;
			
		private:
			bool _applyRenderAttribute(LSPtr<OpenGLRenderEntry> objects, const Scene::LevSceneRenderAttribute& render_attribute);

			int m_current_render_tree_id;
			LSPtr<Scene::LevSceneTreeSearchVisitor> m_searchVisitor;
			LSPtr<Scene::LevSceneTreeTraverseVisitor> m_traverseVisitor;
		};
	}
}