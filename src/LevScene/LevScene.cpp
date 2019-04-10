#include "LevScene.h"
#include "LevSceneData.h"
#include "LevSceneEventListener.h"

namespace Leviathan
{
	namespace Scene
	{
		LevScene::LevScene() 
			:m_sceneType(ELST_UNKNOWN)
			,m_pSceneData(nullptr)
			,m_pEventListener(nullptr)
		{
		}

		bool LevScene::Init(LevSceneType sceneType)
		{
			m_sceneType = sceneType;
			m_pSceneData.Reset(new LevSceneData);
			m_pEventListener.Reset(new LevSceneEventListener(*this));

			return true;
		}

		void LevScene::Update()
		{
			if (m_sceneType == ELST_UNKNOWN)
			{
				return;
			}
		}

		void LevScene::SetViewport(int width, int height)
		{
		}

		LPtr<LevSceneEventListener> LevScene::GetEventListener()
		{
			LEV_ASSERT(m_pEventListener);
			return m_pEventListener;
		}

		const Leviathan::Scene::LevSceneData& LevScene::GetSceneData()
		{
			LEV_ASSERT(m_pSceneData);
			return *m_pSceneData;
		}

	}
}