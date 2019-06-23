#pragma once

#include "LevSceneLogicAttribute.h"
#include <Eigen/Dense>

namespace Leviathan
{
	namespace Scene
	{
		class LEV_SCENE_API LevLAttrLocalTransform : public LevSceneLogicAttribute
		{
		public:
			LevLAttrLocalTransform(const Eigen::Matrix4f& matrix = Eigen::Matrix4f::Identity());
			void SetMatrix(const Eigen::Matrix4f& matrix);
			const Eigen::Matrix4f& GetMatrix() const;

			void Reset();

		private:
			Eigen::Matrix4f m_localMatrix;
		};
	}
}