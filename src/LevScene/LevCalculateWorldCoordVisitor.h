#pragma once

#include "NodeVisitor.h"
#include "LevSceneAPIDefine.h"
#include <vector>
#include <Eigen/Dense>

namespace Leviathan
{
	namespace Scene
	{
		class LevSceneObject;

		class LEV_SCENE_API LevCalculateWorldCoordVisitor : public NodeVisitor<LevSceneObject>
		{
		public:
			void Apply(Node<LevSceneObject>& node);
			void Apply(const Node<LevSceneObject>& node);

		private:
			std::vector<Eigen::Matrix4f> m_stack;
		};
	}
}