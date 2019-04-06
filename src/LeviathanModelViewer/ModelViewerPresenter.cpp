#include <cassert>
#include "ModelViewerPresenter.h"
#include "ModelViewerUserInterface.h"
#include "RenderService.h"
#include "GlobalDef.h"
#include "UserInterface.h"

using namespace Leviathan;

// ModelViewerPresenter::ModelViewerPresenter() :
// 	m_appState(EAS_UNINITED)
// {
// 
// }
// 
// ModelViewerPresenter::~ModelViewerPresenter()
// {
// 	UnInit();
// }
// 
// ModelViewerPresenter& ModelViewerPresenter::Instance()
// {
// 	return Singleton<ModelViewerPresenter>::Instance();
// }
// 
// AppState ModelViewerPresenter::GetCurrentAppState()
// {
// 	return m_appState;
// }
// 
// bool ModelViewerPresenter::Init(int width, int height, int handle /*= NULL*/)
// {
// 	m_appState = EAS_INITING;
// 	EXIT_IF_FALSE(RenderService().Init(width, height, handle));
// 	m_appState = EAS_INITED;
// 
// 	return true;
// }
// 
// void ModelViewerPresenter::Run()
// {
// 	if (m_appState != EAS_INITED) return;
// 	m_appState = EAS_RUNNING;
// 	RenderService().Run();
// }
// 
// void ModelViewerPresenter::Stop()
// {
// 	m_appState = EAS_STOPPING;
// 	RenderService().SyncStop();
// 	m_appState = EAS_STOPPED;
// }
// 
// bool ModelViewerPresenter::UnInit()
// {
// 	return true;
// }
// 
// int ModelViewerPresenter::GetWindowHandle()
// {
// 	return RenderService().GetWindowHandle();
// }
// 
// bool ModelViewerPresenter::LoadFile(const char * filePath)
// {
// 	auto& scene = ModelViewerPresenter::Instance().RenderService().GetScene();
// 	Leviathan::TriDScene* pTriDScene = dynamic_cast<Leviathan::TriDScene*>(scene.Get());
// 	EXIT_IF_FALSE(pTriDScene);
// 	std::string path = filePath;
// 
// 	Leviathan::SceneDataRequestFunc func = [this, path, pTriDScene]() 
// 	{
// 		pTriDScene->AddMesh(path.c_str(), true);
// 	};
// 
// 	pTriDScene->AddRequest(func);
// 
// 	return true;
// }
// 
// Leviathan::RenderService& ModelViewerPresenter::RenderService()
// {
// 	return Leviathan::RenderService::Instance();
// }
// 
// const Leviathan::RenderService & ModelViewerPresenter::RenderService() const
// {
// 	return Leviathan::RenderService::Instance();
// }

ModelViewerPresenter2::~ModelViewerPresenter2()
{
	UnInit();
}

ModelViewerPresenter2& ModelViewerPresenter2::Instance()
{
	return Singleton<ModelViewerPresenter2>::Instance();
}

Leviathan::AppState ModelViewerPresenter2::GetCurrentAppState()
{
	return m_appState;
}

bool ModelViewerPresenter2::Init(int width, int height, int handle /*= NULL*/)
{
	m_appState = EAS_INITING;
	UserInterface::Init(width, height, handle);
	m_appState = EAS_INITED;

	return true;
}

void ModelViewerPresenter2::Run()
{
	while (true)
	{
		UserInterface::UpdatePresenter();
	}
}

void ModelViewerPresenter2::Stop()
{
	UserInterface::Stop();
}

bool ModelViewerPresenter2::UnInit()
{
	return true;
}

int ModelViewerPresenter2::GetWindowHandle()
{
	return UserInterface::GetData().windowHandle;
}

bool ModelViewerPresenter2::LoadFile(const char* filePath)
{
	return UserInterface::LoadFile(filePath);
}

ModelViewerPresenter2::ModelViewerPresenter2():
	m_appState(EAS_UNINITED)
{

}
