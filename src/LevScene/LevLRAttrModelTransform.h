#pragma once

#include "LevSceneLogicAttribute.h"
#include "LevSceneRenderAttribute.h"
#include <Eigen/Dense>

namespace Leviathan
{
	namespace Scene
	{
		class LevLRAttrModelTransform : public LevSceneLogicAttribute, public LevSceneRenderAttribute
		{
		public:
			LevLRAttrModelTransform(const Eigen::Matrix4f& trans = Eigen::Matrix4f::Identity());
			void SetModelTransform(const Eigen::Matrix4f& trans);
			const Eigen::Matrix4f& GetTransform() const;

		private:
			Eigen::Matrix4f m_trans;
		};
	}
}