#include "LevSceneData.h"
#include "LevSceneTree.h"
#include "LevSceneNode.h"
#include "LevCamera.h"
#include "LevMeshObject.h"

namespace Leviathan
{
	namespace Scene
	{
		LevSceneData::LevSceneData()
			: m_pSceneTree(new LevSceneTree)
			, m_modified(true)
			, m_pCamera(nullptr)
		{
			// FOR DEBUG
			LPtr<LevCamera> pCamera = new LevCamera;
			float eye[3] = { 0.0f, 0.0f, -10.0f };
			float up[3] = { 0.0f, 1.0f, 0.0f };
			float look[3] = { 0.0f, 0.0f, 1.0f };
			LEV_ASSERT(pCamera->Set(eye, look, up, 90.0f, 1.0f, 0.01f, 1000.0f));
			LEV_ASSERT(SetCamera(pCamera));

			LPtr<LevSceneObject> pSceneObject = new LevSceneObject(LSOT_DYNAMIC);
			LPtr<LevMeshObject> pMeshObj = new LevMeshObject();
			LEV_ASSERT(pMeshObj->LoadMeshFile("C:\\Users\\wangjie\\Documents\\Leviathan\\bin\\x64\\Debug\\Models\\SoccerBall.STL"));
			pSceneObject->SetObjectDesc(TryCast<LevMeshObject, LevSceneObjectDescription>(pMeshObj));
			LPtr<LevSceneNode> pMeshNode = new LevSceneNode(pSceneObject);
			m_pSceneTree->AddNode(pMeshNode);
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

		void LevSceneData::ResetModified()
		{
			m_modified = false;
		}

		LPtr<LevCamera> LevSceneData::GetCamera()
		{
			return m_pCamera;
		}

		bool LevSceneData::SetCamera(LPtr<LevCamera> pCamera)
		{
			LEV_ASSERT(!m_pCamera);

			LPtr<LevSceneNode> pNode = new LevSceneNode(TryCast<LevCamera, LevSceneObject>(pCamera));
			EXIT_IF_FALSE(m_pSceneTree->AddNode(pNode));

			m_pCamera.Reset(pCamera);

			return true;
		}

		const std::vector<LPtr<LevLight>> LevSceneData::GetLights() const
		{
			return m_pLights;
		}

		bool LevSceneData::AddLight(LPtr<LevLight> pLight)
		{
			LEV_ASSERT(pLight);

			LPtr<LevSceneNode> pNode = new LevSceneNode(TryCast<LevLight, LevSceneObject>(pLight));
			EXIT_IF_FALSE(m_pSceneTree->AddNode(pNode));

			m_pLights.push_back(pLight);

			return true;
		}

	}
}