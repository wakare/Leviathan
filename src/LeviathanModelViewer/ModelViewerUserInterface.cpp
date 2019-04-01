#include <cassert>
#include "ModelViewerUserInterface.h"
#include "ModelViewerPresenter.h"
#include "RenderService.h"
#include "TriDScene.h"

bool ModelViewerUserInterface::LoadFile(const char * fileName)
{
	/*return _scene().AddMesh(fileName, true);*/
	return false;
}

ModelViewerUserInterface& ModelViewerUserInterface::Instance()
{
	return Singleton<ModelViewerUserInterface>::Instance();
}

ModelViewerUserInterface::ModelViewerUserInterface()
{

}

// Leviathan::TriDScene& ModelViewerUserInterface::_scene()
// {
// 	auto& scene = ModelViewerPresenter::Instance().RenderService().GetScene();
// 	Leviathan::TriDScene* pTriDScene = dynamic_cast<Leviathan::TriDScene*>(scene.Get());
// 	assert(pTriDScene);
// 
// 	return *pTriDScene;
// }
