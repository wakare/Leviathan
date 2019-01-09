#include <memory>
#include <iostream>
#include "RenderService.h"

using namespace Leviathan;

int main()
{
	RenderService::SetSceneType(IScene::EST_POINTCLOUD);
	EXIT_GET_FALSE(RenderService::Instance()->Init());
	RenderService::Instance()->Run();
}

