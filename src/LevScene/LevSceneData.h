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

			LevSceneTree& GetSceneTree();
			const LevSceneTree& GetSceneTree() const;

		private:
			LPtr<LevSceneTree> m_pSceneTree;
		};
	}
}