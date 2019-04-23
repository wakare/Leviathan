#include "LevLRAttrWorldTransform.h"

namespace Leviathan
{
	namespace Scene
	{
		LevLRAttrWorldTransform::LevLRAttrWorldTransform(const Eigen::Matrix4f & trans)
			: LevSceneObjectAttribute(ELSOAT_LOGIC | ELSOAT_RENDER)
		{
			SetWorldTransform(trans);
		}

		void LevLRAttrWorldTransform::SetWorldTransform(const Eigen::Matrix4f & trans)
		{
			m_trans = trans;
		}

		const Eigen::Matrix4f & LevLRAttrWorldTransform::GetTransform() const
		{
			return m_trans;
		}
	}
}


