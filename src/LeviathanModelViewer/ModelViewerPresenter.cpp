#include "ModelViewerPresenter.h"
#include "RenderService.h"

ModelViewerPresenter& ModelViewerPresenter::Instance()
{
	return Singleton<ModelViewerPresenter>::Instance();
}

AppState ModelViewerPresenter::GetCurrentAppState()
{
	return m_appState;
}

bool ModelViewerPresenter::Init(int handle /*= NULL*/)
{
	m_appState = EAS_INITING;
	{
		// 0. Attach window
		_renderService().SetSceneType(IScene::EST_TRID);
		EXIT_IF_FALSE(_renderService().Init(handle));

		// 1. Create user-data
		/*_renderService().GetScene()->GetSceneData().AddNode()*/
	}
	m_appState = EAS_INITED;

	return true;
}

void ModelViewerPresenter::Run()
{
	if (m_appState != EAS_INITED) return;
	m_appState = EAS_RUNNING;
	_renderService().Run();
}

void ModelViewerPresenter::Stop()
{
	m_appState = EAS_STOPPING;
	_renderService().SyncStop();
	m_appState = EAS_STOPPED;
}

bool ModelViewerPresenter::UnInit()
{
	return true;
}

ModelViewerPresenter::ModelViewerPresenter():
	m_appState(EAS_UNINITED)
{
}

ModelViewerPresenter::~ModelViewerPresenter()
{
	UnInit();
}

RenderService & ModelViewerPresenter::_renderService()
{
	return *RenderService::Instance();
}

