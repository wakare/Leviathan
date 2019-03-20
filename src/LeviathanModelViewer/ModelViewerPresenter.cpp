#include <cassert>
#include "ModelViewerPresenter.h"
#include "ModelViewerUserInterface.h"
#include "RenderService.h"
#include "GlobalDef.h"

ModelViewerPresenter::ModelViewerPresenter() :
	m_appState(EAS_UNINITED)
{

}

ModelViewerPresenter::~ModelViewerPresenter()
{
	UnInit();
}

ModelViewerPresenter& ModelViewerPresenter::Instance()
{
	return Singleton<ModelViewerPresenter>::Instance();
}

AppState ModelViewerPresenter::GetCurrentAppState()
{
	return m_appState;
}

bool ModelViewerPresenter::Init(int width, int height, int handle /*= NULL*/)
{
	m_appState = EAS_INITING;

	{
		EXIT_IF_FALSE(RenderService().Init(width, height, handle));
	}

	m_appState = EAS_INITED;

	return true;
}

void ModelViewerPresenter::Run()
{
	if (m_appState != EAS_INITED) return;
	m_appState = EAS_RUNNING;
	RenderService().Run();
}

void ModelViewerPresenter::Stop()
{
	m_appState = EAS_STOPPING;
	RenderService().SyncStop();
	m_appState = EAS_STOPPED;
}

bool ModelViewerPresenter::UnInit()
{
	return true;
}

int ModelViewerPresenter::GetWindowHandle() const
{
	return RenderService().GetWindowHandle();
}

bool ModelViewerPresenter::LoadFile(const char * filePath)
{
	auto& scene = ModelViewerPresenter::Instance().RenderService().GetScene();
	Leviathan::TriDScene* pTriDScene = dynamic_cast<Leviathan::TriDScene*>(scene.Get());
	EXIT_IF_FALSE(pTriDScene);
	std::string path = filePath;

	Leviathan::SceneDataRequestFunc func = [this, path, pTriDScene]() 
	{
		pTriDScene->AddMesh(path.c_str(), true);
	};

	pTriDScene->AddRequest(func);

	return true;
}

Leviathan::RenderService& ModelViewerPresenter::RenderService()
{
	return Leviathan::RenderService::Instance();
}

const Leviathan::RenderService & ModelViewerPresenter::RenderService() const
{
	return Leviathan::RenderService::Instance();
}

