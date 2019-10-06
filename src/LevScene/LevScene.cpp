#include "LevScene.h"
#include "LevSceneData.h"
#include "LevCamera.h"
#include "LevSceneEventListener.h"

namespace Leviathan
{
	namespace Scene
	{
		LevScene::LevScene() 
			: m_sceneType(ELST_UNKNOWN)
			, m_pSceneData(nullptr)
			, m_pEventListener(nullptr)
			, m_inited(false)
		{
		}

		LevScene::~LevScene()
		{
		}

		bool LevScene::Init(LevSceneType sceneType)
		{
			if (m_inited)
			{
				return false;
			}

			m_sceneType = sceneType;
			m_pSceneData.Reset(new LevSceneData);
			m_pEventListener.Reset(new LevSceneEventListener(*this));
			m_inited = true;

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

		void LevScene::Update()
		{
			m_pSceneData->UpdateTimer();

			m_pSceneData->DoUserUpdateCallback();

			if (HasModified())
			{
				for (auto& callback : m_scene_modified_callbacks)
				{
					callback();
				}
			}
		}

		void LevScene::SetNodeModified()
		{
			m_pSceneData->SetModified();
		}

		void LevScene::SetViewport(int width, int height)
		{
			m_pSceneData->GetMainCamera()->Set(ANGLE_TO_RADIAN(60.0f), (1.0f * width) / height, 0.01f, 10000.0f);
		}

		bool LevScene::HasModified() const
		{
			return m_pSceneData->HasModified();
		}

		LSPtr<LevSceneEventListener> LevScene::GetEventListener()
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

		void LevScene::RegisterModifiedCallback(LevSceneModifiedCallback callback)
		{
			m_scene_modified_callbacks.push_back(callback);
		}

	}
}