#include "LevSceneObject.h"
#include "GlobalDef.h"
#include "LevSceneObjectDescription.h"

namespace Leviathan
{
	namespace Scene
	{
		LevSceneObject::LevSceneObject(LevSceneObjectType type) :
			m_type(type)
		{

		}

		LevSceneObjectType LevSceneObject::GetType() const
		{
			return m_type;
		}

		bool LevSceneObject::AddAttribute(LPtr<LevSceneObjectAttribute> pAttribute)
		{
			m_pAttributes.push_back(pAttribute);
			return true;
		}

		const std::vector<LPtr<LevSceneObjectAttribute>>& LevSceneObject::GetObjAttributes() const
		{
			return m_pAttributes;
		}

		bool LevSceneObject::SetObjectDesc(LPtr<LevSceneObjectDescription> pObjDesc)
		{
			m_pObjDesc.Reset(pObjDesc);
			return true;
		}

		const LevSceneObjectDescription & LevSceneObject::GetObjDesc() const
		{
			LEV_ASSERT(m_pObjDesc.Get());
			return *m_pObjDesc;
		}

	}
}