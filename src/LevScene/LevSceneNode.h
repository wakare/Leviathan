#pragma once

#include "Node.h"
#include "LevSceneAPIDefine.h"

namespace Leviathan
{
	namespace Scene
	{
		class LevSceneObject;

		class LEV_SCENE_API LevSceneNode : public Node<LevSceneObject>
		{
		public:
			LevSceneNode(LSPtr<LevSceneObject> pSceneNodeData);
			Node<LevSceneObject>& ToBase();

			void AddChild(LSPtr<LevSceneNode> child_node);
			void DelChild(LSPtr<LevSceneNode> child_node);
			void SetParent(LSPtr<LevSceneNode> parent_node);

			bool HasModified() const;
			void SetModified(bool bRecursion = true);
		};
	}
}