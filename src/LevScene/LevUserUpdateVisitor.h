#pragma once

#include "NodeVisitor.h"
#include "LevSceneAPIDefine.h"
#include <functional>

namespace Leviathan
{
	namespace Scene
	{
		class LevSceneObject;

		class LEV_SCENE_API LevUserUpdateVisitor : public NodeVisitor<LevSceneObject>
		{
		public:
			void Apply(Node<LevSceneObject>& node) override;
			void Apply(const Node<LevSceneObject>& node) override;
		};
	}
}

