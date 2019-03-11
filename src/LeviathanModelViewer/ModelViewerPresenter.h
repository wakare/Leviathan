#pragma once
#include "Singleton.h"
#include "RenderService.h"
#include "ModelViewerUserInterface.h"

enum AppState
{
	EAS_UNINITED,
	EAS_INITING,
	EAS_INITED,
	EAS_RUNNING,
	EAS_STOPPING,
	EAS_STOPPED
};

//class ModelViewerUserInterface;

//namespace Leviathan
//{
//	class RenderService;
//}

class ModelViewerPresenter 
{
	DECLARE_SELF_TO_SINGLETON(ModelViewerPresenter)

public:
	~ModelViewerPresenter();
	static ModelViewerPresenter& Instance();
	AppState GetCurrentAppState();

	bool Init(int handle = NULL);
	void Run();
	void Stop();
	bool UnInit();

	bool LoadFile(const char* filePath);

	Leviathan::RenderService& RenderService();
	
private:
	ModelViewerPresenter();
	//ModelViewerUserInterface& _userInterface();


	AppState m_appState;
};