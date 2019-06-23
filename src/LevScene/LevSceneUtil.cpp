#include "LevSceneUtil.h"
#include "LevMeshObject.h"
#include "LevSceneObject.h"

namespace Leviathan
{
	namespace Scene
	{
		bool LevSceneUtil::InitSceneNodeWithMeshFile(const char * mesh_file, unsigned scene_object_mask, LPtr<LevSceneNode>& out_scene_node)
		{
			LPtr<LevMeshObject> mesh_object = new LevMeshObject;
			EXIT_IF_FALSE(mesh_object->LoadMeshFile(mesh_file));

			LPtr<LevSceneObject> scene_object = new LevSceneObject(scene_object_mask);
			EXIT_IF_FALSE(scene_object->SetObjectDesc(TryCast<LevMeshObject, LevSceneObjectDescription>(mesh_object)));

			out_scene_node.Reset(new LevSceneNode(scene_object));
			return true;
		}
	}
}