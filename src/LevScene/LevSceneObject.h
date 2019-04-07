#pragma once

#include <vector>
#include "LPtr.h"

namespace Leviathan
{
	namespace Scene
	{
		enum LevSceneObjectType
		{
			LSOT_STATIC,
			LSOT_DYNAMIC,
			LSOT_UNRENDERABLE
		};

		class LevSceneObjectAttribute;

		class LevSceneObject
		{
		public:
			LevSceneObject(LevSceneObjectType type);
			bool AddAttribute(LPtr<LevSceneObjectAttribute> pAttribute);

		private:
			const LevSceneObjectType m_type;
			std::vector<LPtr<LevSceneObjectAttribute>> m_pAttributes;
		};
	}
}