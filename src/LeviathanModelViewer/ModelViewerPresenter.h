#pragma once
#include "Singleton.h"
#include "RenderService.h"

using namespace Leviathan;

enum AppState
{
	EAS_UNINITED,
	EAS_INITING,
	EAS_INITED,
	EAS_RUNNING,
	EAS_STOPPING,
	EAS_STOPPED
};

class ModelViewerPresenter 
{
	DECLARE_SELF_TO_SINGLETON(ModelViewerPresenter)
public:
	static ModelViewerPresenter& Instance();
	AppState GetCurrentAppState();

	bool Init(int handle = NULL);
	void Run();
	void Stop();
	bool UnInit();

private:
	ModelViewerPresenter();
	~ModelViewerPresenter();
	RenderService& _renderService();

	AppState m_appState;
};