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
	bool LoadFile(const char* filePath);

	//Leviathan::RenderService& RenderService();
	//const Leviathan::RenderService& RenderService() const;
	const Leviathan::AppState& GetAppState();

private:
	ModelViewerPresenter();
	Leviathan::UserInterface& _userInterface();
};