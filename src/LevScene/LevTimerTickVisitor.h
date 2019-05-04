#pragma once

#include "NodeVisitor.h"

namespace Leviathan
{
	namespace Scene
	{
		class LevSceneObject;

		class LevTimerTickVisitor : public NodeVisitor<LevSceneObject>
		{
		public:
			virtual void Apply(Node<LevSceneObject>& node);
			virtual void Apply(const Node<LevSceneObject>& node);
		};
	}
}