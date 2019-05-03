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
			void SetMatrix(const Eigen::Matrix4f& trans);
			const Eigen::Matrix4f& GetMatrix() const;

			void Reset();

		private:
			Eigen::Matrix4f m_trans;
		};
	}
}