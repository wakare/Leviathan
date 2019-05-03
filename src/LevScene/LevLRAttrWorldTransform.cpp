#include "LevLRAttrWorldTransform.h"

namespace Leviathan
{
	namespace Scene
	{
		LevLRAttrWorldTransform::LevLRAttrWorldTransform(const Eigen::Matrix4f & trans)
			: LevSceneObjectAttribute(ELSOAT_LOGIC | ELSOAT_RENDER)
		{
			SetMatrix(trans);
		}

		void LevLRAttrWorldTransform::SetMatrix(const Eigen::Matrix4f & trans)
		{
			m_trans = trans;
		}

		const Eigen::Matrix4f & LevLRAttrWorldTransform::GetMatrix() const
		{
			return m_trans;
		}

		void LevLRAttrWorldTransform::Reset()
		{
			SetMatrix(Eigen::Matrix4f::Identity());
		}
	}
}


