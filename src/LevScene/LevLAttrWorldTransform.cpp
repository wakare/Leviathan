#include "LevLAttrWorldTransform.h"

namespace Leviathan
{
	namespace Scene
	{
		LevLAttrWorldTransform::LevLAttrWorldTransform(const Eigen::Matrix4f & trans)
		{
			SetWorldTransform(trans);
		}

		void LevLAttrWorldTransform::SetWorldTransform(const Eigen::Matrix4f & trans)
		{
			m_trans = trans;
		}

		const Eigen::Matrix4f & LevLAttrWorldTransform::GetTransform() const
		{
			return m_trans;
		}
	}
}


