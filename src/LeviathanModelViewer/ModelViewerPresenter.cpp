#include <cassert>
#include "ModelViewerPresenter.h"
#include "ModelViewerUserInterface.h"
#include "RenderService.h"
#include "GlobalDef.h"
#include "LevRuntimeInterface.h"

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
	LevRuntimeInterface::Init(width, height, handle);
	m_appState = EAS_INITED;

	return true;
}

void ModelViewerPresenter::Run()
{
	m_appState = EAS_RUNNING;
	while (true)
	{
		LevRuntimeInterface::Update();
	}
}

void ModelViewerPresenter::Stop()
{
	LevRuntimeInterface::Stop();
}

bool ModelViewerPresenter::UnInit()
{
	return true;
}

int ModelViewerPresenter::GetWindowHandle()
{
	return LevRuntimeInterface::GetRuntimeData().windowHandle;
}

bool ModelViewerPresenter::LoadMeshFile(const char* filePath)
{
	return LevRuntimeInterface::LoadMesh(filePath);
}

bool ModelViewerPresenter::LoadPointCloudFile(const char* filePath)
{
	LPtr<Scene::LevSceneNode> pNode;
	return LevRuntimeInterface::LoadPointCloud(filePath, pNode);
}

ModelViewerPresenter::ModelViewerPresenter():
	m_appState(EAS_UNINITED)
{

}
