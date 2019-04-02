#pragma once
#include "Singleton.h"

namespace Leviathan
{
	class UserInterface;
	enum AppState;
}

class ModelViewerPresenter 
{
	DECLARE_SELF_TO_SINGLETON(ModelViewerPresenter)

public:
	~ModelViewerPresenter();
	static ModelViewerPresenter& Instance();
	//AppState GetCurrentAppState();

	bool Init(int width, int height, int handle = NULL);
	void Run();
	void Stop();
	bool UnInit();

	int GetWindowHandle() ;
	const Leviathan::AppState& GetAppState();
	Leviathan::UserInterface& GetUserInterface();

private:
	ModelViewerPresenter();
};