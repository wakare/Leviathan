#pragma once

#include <functional>
#include <vector>

#include "LSPtr.h"
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
			virtual ~LevScene();

			bool Init(LevSceneType sceneType);
			void UpdateNodeState();
			void UpdateWorldTransform();
			virtual void Update();
			void SetNodeModified();
			void SetViewport(int width, int height);

			bool HasModified() const;
			void ResetModified();

			void RegisterModifiedCallback(LevSceneModifiedCallback callback);

			LSPtr<LevSceneEventListener> GetEventListener();
			const LevSceneData& GetSceneData() const;
			LevSceneData& GetSceneData();

		protected:
			bool m_inited;
			LevSceneType m_sceneType;
			LSPtr<LevSceneData> m_pSceneData;
			LSPtr<LevSceneEventListener> m_pEventListener;

			std::vector<LevSceneModifiedCallback> m_scene_modified_callbacks;
		};
	}
}