#include "LevSceneObjectDescription.h"

namespace Leviathan
{
	namespace Scene
	{
		LevSceneObjectDescription::LevSceneObjectDescription(LevSceneObjectDescType descType):
			m_type(descType)
		{
		}

		LevSceneObjectDescription::~LevSceneObjectDescription()
		{

		}

		LevSceneObjectDescType LevSceneObjectDescription::GetType() const
		{
			return m_type;
		}


	}
}