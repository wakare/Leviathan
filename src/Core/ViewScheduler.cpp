#include "ViewScheduler.h"
#include "RenderWindow.h"
#include "LevSceneNode.h"
#include "LevSceneData.h"
#include "MeshImpl.h"
#include "LevMeshObject.h"
#include "LevSceneObject.h"
#include "ToolModule.h"
#include "PresenterScheduler.h"

namespace Leviathan
{
	ViewScheduler::ViewScheduler()
		: m_done(false)
		, m_pView(nullptr)
	{
		auto _mainLoop = [this](CoPullType<int>& sink)
		{
			while (!m_done)
			{
				if (m_pView)
				{
					m_pView->Update();
				}

				sink();
			}

			LogLine("[VIEW_MAIN_LOOP] Exit!");
		}; 

		DoAsyncTask(_mainLoop);
	}

	void ViewScheduler::Update()
	{
		_tick();
	}

	void ViewScheduler::SetDone()
	{
		m_done = true;
	}

	bool ViewScheduler::Sync_Init(int width, int height, int parentHandle)
	{
		m_pView.reset(new View());
		EXIT_IF_FALSE(m_pView->Init(width, height, parentHandle));

		return true;
	}

	int ViewScheduler::Sync_GetWindowHandle()
	{
		return m_pView->GetWindowHandle();
	}

	bool ViewScheduler::Async_LoadMeshFile(const char* file)
	{
		std::string path(file);

		DoAsyncTask([this, path](CoPullType<int>& sink)
			{
				m_pView->LoadMesh(path.c_str());
			});

		return true;
	}

	bool ViewScheduler::Sync_LoadPointCloudFile(const char* file, LPtr<Scene::LevSceneNode>& out)
	{
		// Check call thread is the same as create thread
		EXIT_IF_FALSE(!IsCreateThread());

		std::string path(file);
		out = m_pView->LoadPointCloud(path.c_str());
		DoSyncTask([this, &path, &out](CoPullType<int>& sink)
			{
				out = m_pView->LoadPointCloud(path.c_str());
			});

		return true;
	}

	bool ViewScheduler::Sync_LoadPointCloud(const PointCloudf& point_cloud, LPtr<Scene::LevSceneNode>& out)
	{
		// Check call thread is the same as create thread
		EXIT_IF_FALSE(!IsCreateThread());
		DoSyncTask([this, &point_cloud, &out](CoPullType<int>& sink)
			{
				out = m_pView->LoadPointCloud(point_cloud);
			});

		return true;
	}

	bool ViewScheduler::Async_AddNode(LPtr<Scene::LevSceneNode> pNode)
	{
		DoAsyncTask([this, pNode] (CoPullType<int>& sink)
			{
				auto& sceneData = m_pView->GetSceneData();
				sceneData.AddSceneNode(pNode);
			});

		return true;
	}

	bool ViewScheduler::Async_LoadCustomMesh(LPtr<IMesh> pMesh)
	{
		LPtr<Scene::LevMeshObject> pMeshObject = new Scene::LevMeshObject();
		pMeshObject->SetMesh(pMesh);

		LPtr<Scene::LevSceneObject> pObject = new Scene::LevSceneObject(Scene::ELSOT_DYNAMIC);
		pObject->SetObjectDesc(TryCast<Scene::LevMeshObject, Scene::LevSceneObjectDescription>(pMeshObject));

		LPtr<Scene::LevSceneNode> pNode = new Scene::LevSceneNode(pObject);
		DoAsyncTask([this, pNode](Leviathan::CoPullType<int>&)
			{
				Async_AddNode(pNode);
			});

		return true;
	}

}
