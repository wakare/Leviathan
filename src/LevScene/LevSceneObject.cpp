#include "LevSceneObject.h"

namespace Leviathan
{
	namespace Scene
	{
		LevSceneObject::LevSceneObject(LevSceneObjectType type) :
			m_type(type)
		{

		}

		bool LevSceneObject::AddAttribute(LPtr<LevSceneObjectAttribute> pAttribute)
		{
			m_pAttributes.push_back(pAttribute);
			return true;
		}

	}
}