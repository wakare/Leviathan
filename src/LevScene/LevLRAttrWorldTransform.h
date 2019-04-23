#pragma once

#include <Eigen/Dense>
#include "LevSceneLogicAttribute.h"
#include "LevSceneRenderAttribute.h"

namespace Leviathan
{
	namespace Scene
	{
		class LevLRAttrWorldTransform : public LevSceneLogicAttribute, public LevSceneRenderAttribute
		{
		public:
			LevLRAttrWorldTransform(const Eigen::Matrix4f& trans = Eigen::Matrix4f::Identity());
			void SetWorldTransform(const Eigen::Matrix4f& trans);
			const Eigen::Matrix4f& GetTransform() const;

		private:
			Eigen::Matrix4f m_trans;
		};
	}
}
