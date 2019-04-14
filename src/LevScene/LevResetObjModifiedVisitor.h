#pragma once

#include "NodeVisitor.h"

namespace Leviathan
{
	template<class T>
	class Node;

	namespace Scene
	{
		class LevSceneObject;

		class LevResetObjModifiedVisitor : public NodeVisitor<LevSceneObject>
		{
		public:
			void Apply(Node<LevSceneObject>& node);
			void Apply(const Node<LevSceneObject>& node);
		};
	}
}