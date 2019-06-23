#pragma once

#include "NodeVisitor.h"
#include "LevSceneAPIDefine.h"

namespace Leviathan
{
	namespace Scene
	{
		class LevSceneObject;

		class LEV_SCENE_API LevTimerTickVisitor : public NodeVisitor<LevSceneObject>
		{
		public:
			virtual void Apply(Node<LevSceneObject>& node);
			virtual void Apply(const Node<LevSceneObject>& node);
		};
	}
}