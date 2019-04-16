#include <cassert>
#include "ModelViewerPresenter.h"
#include "ModelViewerUserInterface.h"
#include "RenderService.h"
#include "GlobalDef.h"
#include "UserInterface.h"

using namespace Leviathan;

ModelViewerPresenter::~ModelViewerPresenter()
{
	UnInit();
}

ModelViewerPresenter& ModelViewerPresenter::Instance()
{
	return Singleton<ModelViewerPresenter>::Instance();
}

Leviathan::AppState ModelViewerPresenter::GetCurrentAppState()
{
	return m_appState;
}

bool ModelViewerPresenter::Init(int width, int height, int handle /*= NULL*/)
{
	m_appState = EAS_INITING;
	UserInterface::Init(width, height, handle);
	m_appState = EAS_INITED;

	return true;
}

void ModelViewerPresenter::Run()
{
	m_appState = EAS_RUNNING;
	while (true)
	{
		UserInterface::UpdatePresenter();
	}
}

void ModelViewerPresenter::Stop()
{
	UserInterface::Stop();
}

bool ModelViewerPresenter::UnInit()
{
	return true;
}

int ModelViewerPresenter::GetWindowHandle()
{
	return UserInterface::GetData().windowHandle;
}

bool ModelViewerPresenter::LoadMeshFile(const char* filePath)
{
	return UserInterface::LoadMeshFile(filePath);
}

bool ModelViewerPresenter::LoadPointCloudFile(const char* filePath)
{
	return UserInterface::LoadPointCloudFile(filePath);
}

ModelViewerPresenter::ModelViewerPresenter():
	m_appState(EAS_UNINITED)
{

}
