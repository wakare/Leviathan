#pragma once

#include "LPtr.h"

namespace Leviathan
{
	namespace Scene
	{
		class LevSceneTree;
		class LevCamera;

		class LevSceneData
		{
		public:
			LevSceneData();

			LevSceneTree& GetSceneTree();
			const LevSceneTree& GetSceneTree() const;

			bool HasModified() const;
			void ResetModified();

			LPtr<LevCamera> GetCamera();
			bool SetCamera(LPtr<LevCamera> pCamera);

		private:
			bool m_modified;
			
			LPtr<LevCamera> m_pCamera;
			LPtr<LevSceneTree> m_pSceneTree;
		};
	}
}