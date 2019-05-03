#include "LevSceneData.h"
#include "LevSceneTree.h"
#include "LevSceneNode.h"
#include "LevCamera.h"
#include "LevMeshObject.h"
#include "LevLight.h"
#include "LevPointLight.h"
#include "LevSceneObject.h"

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
			auto pCameraNode = AddCamera(pCamera);
			LEV_ASSERT(pCameraNode);

			LPtr<LevLight> pLight = new LevPointLight(ELSOT_LIGHT | ELSOT_DYNAMIC | ELSOT_UNRENDERABLE);
			pLight->AmbientColor({ 0.2f, 0.2f, 0.2f });
			pLight->DiffuseColor({ 0.5f, 0.5f, 0.5f });
			pLight->SpecularColor({ 1.0f, 1.0f, 1.0f });
			LPtr<LevSceneNode> pLightNode = new LevSceneNode(TryCast<LevLight, LevSceneObject>(pLight));
			pCameraNode->AddChild(TryCast<LevSceneNode, Node<LevSceneObject>>(pLightNode));

			bool _added = AddLight(pLight, pCameraNode);
			LEV_ASSERT(_added);
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

		void LevSceneData::ResetUnModified()
		{
			m_pSceneTree->ResetObjUnModified();
			m_modified = false;
		}

		void LevSceneData::UpdateWorldCoord()
		{
			m_pSceneTree->UpdateWorldCoord();
		}

		LPtr<LevCamera> LevSceneData::GetCamera()
		{
			return m_pCamera;
		}

		Leviathan::LPtr<Leviathan::Scene::LevSceneNode> LevSceneData::AddCamera(LPtr<LevCamera> pCamera)
		{
			LEV_ASSERT(!m_pCamera);

			pCamera->SetModifiedCallback(m_modifiedCallback);
			LPtr<LevSceneNode> pNode = new LevSceneNode(TryCast<LevCamera, LevSceneObject>(pCamera));
			EXIT_IF_FALSE(m_pSceneTree->AddNodeToRoot(pNode));

			m_pCamera.Reset(pCamera);
			return pNode;
		}

		const std::vector<LPtr<LevLight>> LevSceneData::GetLights() const
		{
			return m_pLights;
		}

		bool LevSceneData::AddLight(LPtr<LevLight> pLight, LPtr<LevSceneNode> pParentNode /*= nullptr*/)
		{
			LEV_ASSERT(pLight);

			LPtr<LevSceneNode> pNode = new LevSceneNode(TryCast<LevLight, LevSceneObject>(pLight));
			pLight->SetModifiedCallback(m_modifiedCallback);
			EXIT_IF_FALSE(m_pSceneTree->AddNodeToRoot(pNode));

			m_pLights.push_back(pLight);
			return true;
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

		void LevSceneData::Update()
		{
			m_pSceneTree->Update();
		}
	}
}