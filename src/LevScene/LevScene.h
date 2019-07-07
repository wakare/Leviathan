#pragma once

#include <functional>
#include <vector>

#include "LPtr.h"
#include "GlobalDef.h"
#include "LevSceneAPIDefine.h"

namespace Leviathan
{
	namespace Scene
	{
		class LevSceneData;
		class LevSceneEventListener;

		typedef std::function<void()> LevSceneModifiedCallback;

		class LEV_SCENE_API LevScene
		{
		public:
			LevScene();
			bool Init(LevSceneType sceneType);
			void UpdateNodeState();
			void UpdateWorldTransform();
			virtual void Update();
			void SetNodeModified();
			void SetViewport(int width, int height);

			bool HasModified() const;
			void ResetModified();

			void RegisterModifiedCallback(LevSceneModifiedCallback callback);

			LPtr<LevSceneEventListener> GetEventListener();
			const LevSceneData& GetSceneData() const;
			LevSceneData& GetSceneData();

		private:
			bool m_inited;
			LevSceneType m_sceneType;
			LPtr<LevSceneData> m_pSceneData;
			LPtr<LevSceneEventListener> m_pEventListener;

			std::vector<LevSceneModifiedCallback> m_scene_modified_callbacks;
		};
	}
}