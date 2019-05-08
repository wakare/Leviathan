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
	ViewScheduler::ViewScheduler():
		m_done(false),
		 m_pView(nullptr)
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

		DoTask(_mainLoop);
	}

	void ViewScheduler::Update()
	{
		_tick();
	}

	void ViewScheduler::SetDone()
	{
		m_done = true;
	}

	bool ViewScheduler::Init(int width, int height, int parentHandle)
	{
		m_pView.reset(new View());
		EXIT_IF_FALSE(m_pView->Init(width, height, parentHandle));

		return true;
	}

	int ViewScheduler::GetWindowHandle()
	{
		return m_pView->GetWindowHandle();
	}

	bool ViewScheduler::LoadMeshFile(const char* file)
	{
		std::string path(file);

		DoTask([this, path](CoPullType<int>& sink)
			{
				m_pView->LoadMesh(path.c_str());
			});

		return true;
	}

	bool ViewScheduler::LoadPointCloudFile(const char* file, LPtr<Scene::LevSceneNode>& out)
	{
		std::string path(file);

		// Check call thread is the same as lev main module thread
		auto mainModuleThreadId = PresenterScheduler::Instance().GetToolModule().GetMainModuleThreadID();
		auto callThreadId = std::this_thread::get_id();
		EXIT_IF_FALSE(mainModuleThreadId != callThreadId);

		DoSyncTask([this, &path, &out](CoPullType<int>& sink)
			{
				out = m_pView->LoadPointCloud(path.c_str());
			});

		return true;
	}

	bool ViewScheduler::AddNode(LPtr<Scene::LevSceneNode> pNode)
	{
		DoTask([this, pNode] (CoPullType<int>& sink)
			{
				auto& sceneData = m_pView->GetSceneData();
				sceneData.AddSceneNode(pNode);
			});

		return true;
	}

	bool ViewScheduler::LoadCustomMesh(LPtr<IMesh> pMesh)
	{
		LPtr<Scene::LevMeshObject> pMeshObject = new Scene::LevMeshObject();
		pMeshObject->SetMesh(pMesh);

		LPtr<Scene::LevSceneObject> pObject = new Scene::LevSceneObject(Scene::ELSOT_DYNAMIC);
		pObject->SetObjectDesc(TryCast<Scene::LevMeshObject, Scene::LevSceneObjectDescription>(pMeshObject));

		LPtr<Scene::LevSceneNode> pNode = new Scene::LevSceneNode(pObject);
		DoTask([this, pNode](Leviathan::CoPullType<int>&)
			{
				AddNode(pNode);
			});

		return true;
	}

}
