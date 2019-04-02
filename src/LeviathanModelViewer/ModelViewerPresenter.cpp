#include <cassert>
#include "ModelViewerPresenter.h"
#include "ModelViewerUserInterface.h"
#include "RenderService.h"
#include "GlobalDef.h"
#include "PresenterScheduler.h"
#include "UserInterface.h"

ModelViewerPresenter::ModelViewerPresenter()
{

}

Leviathan::UserInterface& ModelViewerPresenter::GetUserInterface()
{
	return Leviathan::PresenterScheduler::Instance().GetUserInterface();
}

ModelViewerPresenter::~ModelViewerPresenter()
{
	UnInit();
}

ModelViewerPresenter& ModelViewerPresenter::Instance()
{
	return Singleton<ModelViewerPresenter>::Instance();
}

bool ModelViewerPresenter::Init(int width, int height, int handle /*= NULL*/)
{
	Leviathan::PresenterScheduler::Instance().GetUserInterface().Init(width, height, handle);

	return true;
}

void ModelViewerPresenter::Run()
{
	while (true)
	{
		GetUserInterface().UpdatePresenter();
	}
}

void ModelViewerPresenter::Stop()
{
	GetUserInterface().Stop();
}

bool ModelViewerPresenter::UnInit()
{
	return true;
}

int ModelViewerPresenter::GetWindowHandle()
{
	return GetUserInterface().GetData().windowHandle;
}

const Leviathan::AppState& ModelViewerPresenter::GetAppState()
{
	return Leviathan::PresenterScheduler::Instance().GetAppState();
}

