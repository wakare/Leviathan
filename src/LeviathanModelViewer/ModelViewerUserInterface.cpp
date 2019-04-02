#include <cassert>
#include "ModelViewerUserInterface.h"
#include "ModelViewerPresenter.h"
#include "RenderService.h"
#include "TriDScene.h"
#include "PresenterScheduler.h"
#include "UserInterface.h"

bool ModelViewerUserInterface::LoadFile(const char * fileName)
{
	return Leviathan::PresenterScheduler::Instance().GetUserInterface().LoadFile(fileName);
}

ModelViewerUserInterface& ModelViewerUserInterface::Instance()
{
	return Singleton<ModelViewerUserInterface>::Instance();
}

ModelViewerUserInterface::ModelViewerUserInterface()
{

}
