#pragma once
#include "Singleton.h"
#include "RenderService.h"
#include "ModelViewerUserInterface.h"
#include "GlobalDef.h"

class IController
{
public:
	virtual Leviathan::AppState GetCurrentAppState() = 0;
	virtual bool Init(int width, int height, int handle = NULL) = 0;
	virtual void Run() = 0;
	virtual void Stop() = 0;
	virtual bool UnInit() = 0;

	virtual int GetWindowHandle() = 0;
	virtual bool LoadFile(const char* filePath) = 0;
};

// class ModelViewerPresenter : public IController
// {
// 	DECLARE_SELF_TO_SINGLETON(ModelViewerPresenter)
// 
// public:
// 	~ModelViewerPresenter();
// 	static ModelViewerPresenter& Instance();
// 	Leviathan::AppState GetCurrentAppState();
// 
// 	bool Init(int width, int height, int handle = NULL);
// 	void Run();
// 	void Stop();
// 	bool UnInit();
// 
// 	int GetWindowHandle();
// 	bool LoadFile(const char* filePath);
// 
// 	Leviathan::RenderService& RenderService();
// 	const Leviathan::RenderService& RenderService() const;
// 
// private:
// 	ModelViewerPresenter();
// 	Leviathan::AppState m_appState;
// };

namespace Leviathan
{
	class PresenterScheduler;
}

class ModelViewerPresenter2 : public IController
{
	DECLARE_SELF_TO_SINGLETON(ModelViewerPresenter2)

public:
	~ModelViewerPresenter2();
	static ModelViewerPresenter2& Instance();
	Leviathan::AppState GetCurrentAppState();

	bool Init(int width, int height, int handle = NULL);
	void Run();
	void Stop();
	bool UnInit();

	int GetWindowHandle();
	bool LoadFile(const char* filePath);

private:
	ModelViewerPresenter2();
	Leviathan::AppState m_appState;
};
