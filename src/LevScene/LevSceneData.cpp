#include "LevSceneData.h"
#include "LevSceneTree.h"
#include "LevSceneNode.h"
#include "LevCamera.h"
#include "LevMeshObject.h"
#include "LevLight.h"
#include "LevPointLight.h"
#include "LevSceneObject.h"
#include "LevTimer.h"

namespace Leviathan
{
	namespace Scene
	{
		LevSceneData::LevSceneData()
			: m_pSceneTree(new LevSceneTree)
			, m_modified(true)
			, m_pCamera(nullptr)
		{
			m_modifiedCallback = [this](const LevSceneObject& obj)
			{
				m_modified = true;
			};

			// FOR DEBUG
			LPtr<LevCamera> pCamera = new LevCamera;
			Eigen::Vector3f eye = { 0.0f, 0.0f, -10.0f };
			Eigen::Vector3f up = { 0.0f, 1.0f, 0.0f };
			Eigen::Vector3f lookAt = { 0.0f, 0.0f, 1.0f };
			auto _seted = pCamera->Set(eye.data(), lookAt.data(), up.data(), ANGLE_TO_RADIAN(120.0f), 1.0f, 0.01f, 10000.0f);
			LEV_ASSERT(_seted);
			auto pCameraNode = new LevSceneNode(TryCast<LevCamera, LevSceneObject>(pCamera));
			AddSceneNode(pCameraNode);
			RegisterToMainCamera(pCamera);
			LEV_ASSERT(pCameraNode);

 			auto _camera_timeOut = [pCamera](const LevTimer&)
 			{
 				pCamera->MouseRotate(0.01, 0);
 			};
 
 			LPtr<LevTimer> pCameraTimer = new LevTimer(16.6f, _camera_timeOut);
 			//pCamera->SetTimer(pCameraTimer);

			LPtr<LevLight> pLight = new LevPointLight(ELSOT_LIGHT | ELSOT_DYNAMIC | ELSOT_UNRENDERABLE);
			pLight->AmbientColor({ 0.2f, 0.2f, 0.2f });
			pLight->DiffuseColor({ 0.5f, 0.5f, 0.5f });
			pLight->SpecularColor({ 1.0f, 1.0f, 1.0f });
			LPtr<LevSceneNode> pLightNode = new LevSceneNode(TryCast<LevLight, LevSceneObject>(pLight));
			pCameraNode->AddChild(TryCast<LevSceneNode, Node<LevSceneObject>>(pLightNode));

// 			auto _timeOut = [pLight](const LevTimer&)
// 			{
// 				auto localTransform = pLight->GetLocalTransform();
// 				localTransform(0, 3) -= 0.01f;
// 				localTransform(1, 3) -= 0.01f;
// 				localTransform(2, 3) -= 0.01f;
// 				pLight->SetLocalTransform(localTransform);
// 				pLight->SetModified();
// 			};
// 
// 			LPtr<LevTimer> pTimer = new LevTimer(100.0f, _timeOut);
// 			pLight->SetTimer(pTimer);
		}

		LevSceneTree & LevSceneData::GetSceneTree()
		{
			return *m_pSceneTree;
		}

		const Leviathan::Scene::LevSceneTree& LevSceneData::GetSceneTree() const
		{
			return *m_pSceneTree;
		}

		bool LevSceneData::HasModified() const
		{
			return m_modified;
		}

		void LevSceneData::SetModified()
		{
			m_pSceneTree->SetObjModified();
		}

		void LevSceneData::ResetUnModified()
		{
			m_pSceneTree->ResetObjUnModified();
			m_modified = false;
		}

		void LevSceneData::UpdateWorldTransform()
		{
			m_pSceneTree->UpdateWorldCoord();
		}

		void LevSceneData::UpdateTimer()
		{
			m_pSceneTree->UpdateTimer();
		}

		void LevSceneData::RegisterToMainCamera(LPtr<LevCamera> pCamera)
		{
			m_pCamera = pCamera;
		}

		LPtr<LevCamera> LevSceneData::GetCamera()
		{
			return m_pCamera;
		}

		bool LevSceneData::AddSceneNode(LPtr<LevSceneNode> pNode)
		{
			pNode->GetNodeData()->SetModifiedCallback(m_modifiedCallback);
			EXIT_IF_FALSE(m_pSceneTree->AddNodeToRoot(pNode));
			return true;
		}

		void LevSceneData::RemoveAllRenderables()
		{

		}

		void LevSceneData::UpdateNodeState()
		{
			m_pSceneTree->UpdateNodeState();
		}
	}
}