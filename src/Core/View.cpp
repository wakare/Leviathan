#include "View.h"
#include "IRenderer.h"
#include "ViewData.h"
#include "EventSystem.h"
#include "LevScene.h"
#include "LevSceneData.h"
#include "LevSceneEventListener.h"
#include "LevSceneObject.h"
#include "LevMeshObject.h"
#include "LevSceneNode.h"
#include "LevCamera.h"
#include "LevSceneObjectAttribute.h"
#include "LevRAttrObjectColor.h"
#include "ILevWindow.h"

namespace Leviathan
{
	View::View(LevSceneType type /*= ELST_3D_SCENE*/) :
		m_pData(nullptr)
	{
		m_pData.reset(new ViewData(ELRT_OPENGL));

		LPtr<EventListener> eventListener = TryCast<Scene::LevSceneEventListener, EventListener>(m_pData->GetScene().GetEventListener());
		m_pData->GetEventSystem().AddEventListener(INPUT_EVENT, eventListener.Get());
	}

	bool View::Init(int width, int height, int handle)
	{
		EXIT_IF_FALSE(m_pData->GetRenderWindow().Create(width, height, handle));
		EXIT_IF_FALSE(m_pData->InitRenderer());
		return true;
	}

	void View::Update()
	{
		m_pData->GetEventSystem().DispatchEvent();
		m_pData->GetRenderWindow().Update();
		
		if (m_pData->GetScene().HasModified())
		{
			m_pData->GetScene().Update();
			m_pData->GetRenderer().SetInputData(m_pData->GetScene().GetSceneData());
		}
		
		m_pData->GetRenderer().Update();

		// Scene update must be later than render update, because it will overwrite modified state info.
		//m_pData->GetScene().Update();

		m_pData->GetScene().ResetModified();
	}

	void View::SyncStop()
	{
		m_pData->GetRenderWindow().Stop();
	}

	void View::AsyncStop()
	{ 
		m_pData->GetRenderWindow().Stop();
	}

	bool View::AddEventListener(EventType eventType, LPtr<EventListener> listener)
	{
		EXIT_IF_FALSE(listener);
		m_pData->GetEventSystem().AddEventListener(eventType, listener.Get());
		return true;
	}

	int View::GetWindowHandle() const
	{
		return m_pData->GetRenderWindow().GetWindowHandle();
	}

	Scene::LevSceneData & View::GetSceneData()
	{
		return m_pData->GetScene().GetSceneData();
	}

	bool View::LoadMesh(const char* file, bool bResetCamera /*= true*/)
	{
		auto& sceneData = GetSceneData();
		LPtr<Scene::LevSceneObject> pSceneObject = new Scene::LevSceneObject(Scene::ELSOT_DYNAMIC);
		LPtr<Scene::LevMeshObject> pMeshObj = new Scene::LevMeshObject();
		EXIT_IF_FALSE(pMeshObj->LoadMeshFile(file));
		pSceneObject->SetObjectDesc(TryCast<Scene::LevMeshObject, Scene::LevSceneObjectDescription>(pMeshObj));
		LPtr<Scene::LevSceneNode> pMeshNode = new Scene::LevSceneNode(pSceneObject);
		sceneData.AddSceneNode(pMeshNode);

		if (bResetCamera)
		{
			_resetCamera(pMeshObj->GetAABB());
		}

		return true;
	}

	Leviathan::LPtr<Leviathan::Scene::LevSceneNode> View::LoadPointCloud(const char* file, bool bResetCamera /*= true*/)
	{
		auto& sceneData = GetSceneData();
		LPtr<Scene::LevSceneObject> pSceneObject = new Scene::LevSceneObject(Scene::ELSOT_DYNAMIC);
		LPtr<Scene::LevMeshObject> pMeshObj = new Scene::LevMeshObject();
		EXIT_IF_FALSE(pMeshObj->LoadMeshFile(file));

		// Reset primitive type to point
		unsigned totalVertexCount = 0;
		for (auto& pMesh : pMeshObj->GetMesh())
		{
			pMesh->SetPrimitiveType(IMesh::EPT_POINTS);
			pMesh->SetPrimitiveCount(pMesh->GetVertexCount());
			totalVertexCount += pMesh->GetVertexCount();
		}

		pSceneObject->SetObjectDesc(TryCast<Scene::LevMeshObject, Scene::LevSceneObjectDescription>(pMeshObj));
		LPtr<Scene::LevSceneNode> pMeshNode = new Scene::LevSceneNode(pSceneObject);

		// Add color attribute
		LPtr<Scene::LevObjectColorData> pColorData = new Scene::LevObjectColorData();
		pColorData->color_array = new float[3 * totalVertexCount];
		pColorData->color_array_byte_size = 3 * totalVertexCount * sizeof(float);
		for (unsigned i = 0; i < totalVertexCount; i++)
		{
			auto* color = pColorData->color_array + 3 * i;
			float _temp = (i * 1.0f) / totalVertexCount;
			color[0] = _temp;
			color[1] = 1.0f - _temp;
			color[2] = 0.0f;
		}

		EXIT_IF_FALSE(pMeshObj->SetColorData(Scene::ELOCT_COLOR_ARRAY, *pColorData));
		sceneData.AddSceneNode(pMeshNode);

		if (bResetCamera)
		{
			_resetCamera(pMeshObj->GetAABB());
		}

		return pMeshNode;
	}

	void View::RemoveAllRenderables(bool bSync /*= false*/)
	{
		

	}

	void View::_resetCamera(const AABB & aabb)
	{
		Eigen::Vector3f worldCoord; memcpy(&worldCoord[0], aabb.Center(), 3 * sizeof(float));
		GetSceneData().GetCamera()->LookAt(worldCoord, aabb.Radius());
	}

}