#include "LevLAttrModelTransform.h"

namespace Leviathan
{ 
	namespace Scene
	{

		LevLAttrModelTransform::LevLAttrModelTransform(const Eigen::Matrix4f& trans /*= Eigen::Matrix4f::Identity()*/)
		{
			SetModelTransform(trans);
		}

		void LevLAttrModelTransform::SetModelTransform(const Eigen::Matrix4f& trans)
		{
			m_trans = trans;
		}

		const Eigen::Matrix4f& LevLAttrModelTransform::GetTransform() const
		{
			return m_trans;
		}

	}
}