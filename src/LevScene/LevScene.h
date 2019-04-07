#pragma once

#include "LPtr.h"

namespace Leviathan
{
	namespace Scene
	{
		class LevSceneData;

		class LevScene
		{
		public:
			LevScene();

		private:
			LPtr<LevSceneData> m_pSceneData;
		};
	}
}