#include "OpenGLRenderData.h"
#include "LevSceneData.h"
#include "LevSceneTree.h"
#include "LevSceneNode.h"
#include "LevSceneObject.h"
#include "LevMeshObject.h"
#include "OpenGL3DObject.h"

namespace Leviathan
{
	namespace Renderer
	{
		OpenGLRenderData::OpenGLRenderData()
		{
		}
	
		void OpenGLRenderData::UpdateInputData(const Scene::LevSceneData & sceneData)
		{
			auto& sceneTree = sceneData.GetSceneTree();

			auto& sceneObjects = sceneTree.GetNodes();
			for (const auto& sceneObject : sceneObjects)
			{
				const auto& objData = *sceneObject->GetNodeData();
				if (objData.GetType() == Scene::LSOT_UNRENDERABLE)
				{
					continue;
				}

				auto& objDesc = objData.GetObjDesc();
				if (objDesc.GetType() != ELSOD_MESH)
				{
					continue;
				}

				// TODO: change style to get mesh data?
				const Scene::LevMeshObject* pMesh = dynamic_cast<const Scene::LevMeshObject*>(&objDesc);
				if (!pMesh)
				{
					continue;
				}



				auto& attributes = objData.GetObjAttributes();
				// TODO: Handle different attributes
			}
		}

		bool OpenGLRenderData::ConvertMeshToGLObject(const Scene::LevMeshObject & mesh, LPtr<OpenGL3DObject>& out)
		{

			return true;
		}
	}
}


