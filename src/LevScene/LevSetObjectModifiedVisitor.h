#pragma once

#include "NodeVisitor.h"
#include "LevSceneAPIDefine.h"

namespace Leviathan
{
	template<class T>
	class Node;

	namespace Scene
	{
		class LevSceneObject;

		class LEV_SCENE_API LevSetObjModifiedVisitor : public NodeVisitor<LevSceneObject>
		{
		public:
			void Apply(Node<LevSceneObject>& node);
			void Apply(const Node<LevSceneObject>& node);
		};
	}
}