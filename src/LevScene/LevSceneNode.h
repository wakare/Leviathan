#pragma once

#include "Node.h"

namespace Leviathan
{
	namespace Scene
	{
		class LevSceneObject;

		class LevSceneNode : public Node<LevSceneObject>
		{
		public:
			LevSceneNode(LPtr<LevSceneObject> pSceneNodeData);
			Node<LevSceneObject>& ToBase();

			bool HasModified() const;
			void SetModified(bool bRecursion = true);
		};
	}
}