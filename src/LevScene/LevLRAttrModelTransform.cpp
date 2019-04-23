#include "LevLRAttrModelTransform.h"

namespace Leviathan
{ 
	namespace Scene
	{
		LevLRAttrModelTransform::LevLRAttrModelTransform(const Eigen::Matrix4f& trans /*= Eigen::Matrix4f::Identity()*/):
			LevSceneObjectAttribute(ELSOAT_LOGIC | ELSOAT_RENDER)
		{
			SetModelTransform(trans);
		}

		void LevLRAttrModelTransform::SetModelTransform(const Eigen::Matrix4f& trans)
		{
			m_trans = trans;
		}

		const Eigen::Matrix4f& LevLRAttrModelTransform::GetTransform() const
		{
			return m_trans;
		}

	}
}