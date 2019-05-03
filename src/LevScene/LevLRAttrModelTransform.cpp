#include "LevLRAttrModelTransform.h"

namespace Leviathan
{ 
	namespace Scene
	{
		LevLRAttrModelTransform::LevLRAttrModelTransform(const Eigen::Matrix4f& trans /*= Eigen::Matrix4f::Identity()*/):
			LevSceneObjectAttribute(ELSOAT_LOGIC | ELSOAT_RENDER)
		{
			SetMatrix(trans);
		}

		void LevLRAttrModelTransform::SetMatrix(const Eigen::Matrix4f& trans)
		{
			m_trans = trans;
		}

		const Eigen::Matrix4f& LevLRAttrModelTransform::GetMatrix() const
		{
			return m_trans;
		}

		void LevLRAttrModelTransform::Reset()
		{
			SetMatrix(Eigen::Matrix4f::Identity());
		}

	}
}