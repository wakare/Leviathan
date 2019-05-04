#include "LevScene.h"
#include "LevSceneData.h"
#include "LevCamera.h"
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

		void LevScene::UpdateNodeState()
		{
			m_pSceneData->UpdateNodeState();
		}

		void LevScene::UpdateWorldTransform()
		{
			m_pSceneData->UpdateWorldTransform();
		}

		void LevScene::SetViewport(int width, int height)
		{
			m_pSceneData->GetCamera()->Set(ANGLE_TO_RADIAN(120.0f), (1.0f * width) / height, 0.01f, 10000.0f);
		}

		bool LevScene::HasModified() const
		{
			return m_pSceneData->HasModified();
		}

		LPtr<LevSceneEventListener> LevScene::GetEventListener()
		{
			LEV_ASSERT(m_pEventListener);
			return m_pEventListener;
		}

		const Leviathan::Scene::LevSceneData& LevScene::GetSceneData() const
		{
			LEV_ASSERT(m_pSceneData.Get());
			return *m_pSceneData;
		}

		LevSceneData & LevScene::GetSceneData()
		{
			LEV_ASSERT(m_pSceneData.Get());
			return *m_pSceneData;
		}

		void LevScene::ResetModified()
		{
			m_pSceneData->ResetUnModified();
		}

	}
}