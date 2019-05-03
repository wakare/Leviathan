#include "LevLAttrLocalTransform.h"

namespace Leviathan
{
	namespace Scene
	{
		LevLAttrLocalTransform::LevLAttrLocalTransform(const Eigen::Matrix4f& matrix)
			: LevSceneObjectAttribute(ELSOAT_LOGIC)
		{
			SetMatrix(matrix);
		}

		void LevLAttrLocalTransform::SetMatrix(const Eigen::Matrix4f & matrix)
		{
			m_localMatrix = matrix;
		}

		const Eigen::Matrix4f & LevLAttrLocalTransform::GetMatrix() const
		{
			return m_localMatrix;
		}

		void LevLAttrLocalTransform::Reset()
		{
			SetMatrix(Eigen::Matrix4f::Identity());
		}
	}
}