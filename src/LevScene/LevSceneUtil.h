#pragma once

#include "LevSceneAPIDefine.h"
#include "LPtr.h"
#include "LevSceneNode.h"

namespace Leviathan
{
	namespace Scene
	{
		class LEV_SCENE_API LevSceneUtil
		{
		public:
			static bool InitSceneNodeWithMeshFile(const char* mesh_file, unsigned scene_object_mask, LPtr<LevSceneNode>& out_scene_node);
		};
	}
}