#pragma once

#include "NodeVisitor.h"
#include <vector>
#include <Eigen/Dense>

namespace Leviathan
{
	namespace Scene
	{
		class LevSceneObject;

		class LevCalculateWorldCoordVisitor : public NodeVisitor<LevSceneObject>
		{
		public:
			void Apply(Node<LevSceneObject>& node);
			void Apply(const Node<LevSceneObject>& node);

		private:
			std::vector<Eigen::Matrix4f> m_stack;
		};
	}
}