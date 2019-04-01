#include <cassert>
#include "ModelViewerPresenter.h"
#include "ModelViewerUserInterface.h"
#include "RenderService.h"
#include "GlobalDef.h"
#include "PresenterScheduler.h"
#include "UserInterface.h"

ModelViewerPresenter::ModelViewerPresenter()
{

}

Leviathan::UserInterface& ModelViewerPresenter::_userInterface()
{
	return Leviathan::PresenterScheduler::Instance().GetUserInterface();
}

ModelViewerPresenter::~ModelViewerPresenter()
{
	UnInit();
}

ModelViewerPresenter& ModelViewerPresenter::Instance()
{
	return Singleton<ModelViewerPresenter>::Instance();
}

bool ModelViewerPresenter::Init(int width, int height, int handle /*= NULL*/)
{
	/*EXIT_IF_FALSE(RenderService().Init(width, height, handle));*/
	Leviathan::PresenterScheduler::Instance().GetUserInterface().Init(width, height, handle);

	return true;
}

void ModelViewerPresenter::Run()
{
	//if (GetAppState() != EAS_INITED) return;
	//RenderService().Run();

	/*while (GetAppState() == Leviathan::EAS_RUNNING)
	{
	}*/

	while (true)
	{
		_userInterface().UpdatePresenter();
	}
}

void ModelViewerPresenter::Stop()
{
	//m_appState = EAS_STOPPING;
	//RenderService().SyncStop();
	//m_appState = EAS_STOPPED;

	_userInterface().Stop();
}

bool ModelViewerPresenter::UnInit()
{
	return true;
}

int ModelViewerPresenter::GetWindowHandle()
{
	//return RenderService().GetWindowHandle();
	return _userInterface().GetData().windowHandle;
}

bool ModelViewerPresenter::LoadFile(const char * filePath)
{
	/*auto& scene = _userInterface().GetScene();
	Leviathan::TriDScene* pTriDScene = dynamic_cast<Leviathan::TriDScene*>(scene.Get());
	EXIT_IF_FALSE(pTriDScene);
	std::string path = filePath;

	Leviathan::SceneDataRequestFunc func = [this, path, pTriDScene]()
	{
		pTriDScene->AddMesh(path.c_str(), true);
	};

	pTriDScene->AddRequest(func);

	return true;*/

	return false;
}

//Leviathan::RenderService& ModelViewerPresenter::RenderService()
//{
//	return Leviathan::RenderService::Instance();
//}
//
//const Leviathan::RenderService & ModelViewerPresenter::RenderService() const
//{
//	return Leviathan::RenderService::Instance();
//}

const Leviathan::AppState& ModelViewerPresenter::GetAppState()
{
	return Leviathan::PresenterScheduler::Instance().GetAppState();
}

