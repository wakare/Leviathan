#include "LevRAttrWorldTransform.h"

namespace Leviathan
{
	namespace Scene
	{
		LevRAttrWorldTransform::LevRAttrWorldTransform(const Eigen::Matrix4f & trans)
		{
			SetWorldTransform(trans);
		}

		void LevRAttrWorldTransform::SetWorldTransform(const Eigen::Matrix4f & trans)
		{
			m_trans = trans;
		}

		const Eigen::Matrix4f & LevRAttrWorldTransform::GetTransform() const
		{
			return m_trans;
		}
	}
}


