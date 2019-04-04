#pragma once
#include "Singleton.h"
#include "RenderService.h"
#include "ModelViewerUserInterface.h"

class ModelViewerPresenter 
{
	DECLARE_SELF_TO_SINGLETON(ModelViewerPresenter)

public:
	~ModelViewerPresenter();
	static ModelViewerPresenter& Instance();
	AppState GetCurrentAppState();

	bool Init(int width, int height, int handle = NULL);
	void Run();
	void Stop();
	bool UnInit();

	int GetWindowHandle() const;
	bool LoadFile(const char* filePath);

	Leviathan::RenderService& RenderService();
	const Leviathan::RenderService& RenderService() const;

private:
	ModelViewerPresenter();
	AppState m_appState;
};