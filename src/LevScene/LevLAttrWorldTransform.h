#pragma once

#include "LevSceneLogicAttribute.h"
#include <Eigen/Dense>

namespace Leviathan
{
	namespace Scene
	{
		class LevLAttrWorldTransform : public LevSceneLogicAttribute
		{
		public:
			LevLAttrWorldTransform(const Eigen::Matrix4f& trans = Eigen::Matrix4f::Identity());
			void SetWorldTransform(const Eigen::Matrix4f& trans);
			const Eigen::Matrix4f& GetTransform() const;

		private:
			Eigen::Matrix4f m_trans;
		};
	}
}
