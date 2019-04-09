#pragma once

#include "LevSceneLogicAttribute.h"
#include <Eigen/Dense>

namespace Leviathan
{
	namespace Scene
	{
		class LevLAttrWorldCoord : public LevSceneLogicAttribute
		{
		public:
			LevLAttrWorldCoord(float x, float y, float z);
			LevLAttrWorldCoord(float* coord);

			const Eigen::Vector3f& GetCoord() const;
			void SetCoord(float x, float y, float z);
			void SetCoord(float* coord);

		private:
			Eigen::Vector3f m_coord;
		};
	}
}