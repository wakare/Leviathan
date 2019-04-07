#include "LevSceneNode.h"
#include "LevSceneObject.h"

namespace Leviathan
{
	namespace Scene
	{
		LevSceneNode::LevSceneNode(LPtr<LevSceneObject> pSceneNodeData):
			Node<LevSceneObject>(pSceneNodeData)
		{
		}
	}
}