#pragma once

#include "LPtr.h"
#include "GlobalDef.h"

namespace Leviathan
{
	namespace Scene
	{
		class LevSceneData;
		class LevSceneEventListener;

		class LevScene
		{
		public:
			LevScene();
			bool Init(LevSceneType sceneType);
			void UpdateNodeState();
			void UpdateWorldTransform();
			void SetViewport(int width, int height);

			bool HasModified() const;
			void ResetModified();

			LPtr<LevSceneEventListener> GetEventListener();
			const LevSceneData& GetSceneData() const;
			LevSceneData& GetSceneData();

		private:
			LevSceneType m_sceneType;
			LPtr<LevSceneData> m_pSceneData;
			LPtr<LevSceneEventListener> m_pEventListener;
		};
	}
}