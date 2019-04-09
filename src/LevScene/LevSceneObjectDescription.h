#pragma once

#include "GlobalDef.h"

namespace Leviathan
{
	namespace Scene
	{
		class LevSceneObjectDescription
		{
		public:
			LevSceneObjectDescription(LevSceneObjectDescType descType);
			virtual ~LevSceneObjectDescription();

			LevSceneObjectDescType GetType() const;

		private:
			LevSceneObjectDescType m_type;
		};
	}
}