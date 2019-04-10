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

			bool HasModified() const;
			void ResetModified();

		private:
			bool m_modified;
			LPtr<LevSceneTree> m_pSceneTree;
		};
	}
}