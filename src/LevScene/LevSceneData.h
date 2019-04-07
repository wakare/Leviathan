#pragma once

#include "LPtr.h"

namespace Leviathan
{
	namespace Scene
	{
		class LevSceneTree;

		class LevSceneData
		{
		public:
			LevSceneData();
			const LevSceneTree& GetSceneTree();

		private:
			LPtr<LevSceneTree> m_pSceneTree;
		};
	}
}