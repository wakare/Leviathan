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
			LevSceneNode(LPtr<LevSceneObject> pSceneNodeData);
			Node<LevSceneObject>& ToBase();

			void AddChild(LPtr<LevSceneNode> child_node);
			void DelChild(LPtr<LevSceneNode> child_node);
			void SetParent(LPtr<LevSceneNode> parent_node);

			bool HasModified() const;
			void SetModified(bool bRecursion = true);
		};
	}
}