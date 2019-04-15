#include "View.h"
#include "IRenderer.h"
#include "ViewData.h"
#include "EventSystem.h"
#include "LevScene.h"
#include "LevSceneData.h"
#include "LevRenderWindow.h"
#include "LevSceneEventListener.h"
#include "LevSceneObject.h"
#include "LevMeshObject.h"
#include "LevSceneNode.h"
#include "LevCamera.h"

namespace Leviathan
{
	View::View(LevSceneType type /*= ELST_3D_SCENE*/) :
		m_pData(nullptr)
	{
		m_pData.reset(new ViewData(ELRT_OPENGL));

		LPtr<EventListener> eventListener = TryCast<Scene::LevSceneEventListener, EventListener>(m_pData->GetScene().GetEventListener());
		m_pData->GetEventSystem().AddEventListener(INPUT_EVENT, eventListener);
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
		m_pData->GetScene().Update();

		if (m_pData->GetScene().HasModified())
		{
			m_pData->GetRenderer().SetInputData(m_pData->GetScene().GetSceneData());
			m_pData->GetScene().ResetModified();
		}
		
		m_pData->GetRenderer().Update();
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
		m_pData->GetEventSystem().AddEventListener(eventType, listener);
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
			const auto& _meshAABB = pMeshObj->GetAABB();
			Eigen::Vector3f worldCoord; memcpy(&worldCoord[0], _meshAABB.Center(), 3 * sizeof(float));
			sceneData.GetCamera()->LookAt(worldCoord, _meshAABB.Radius());
		}

		return true;
	}
}