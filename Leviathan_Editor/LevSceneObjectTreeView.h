#pragma once
#include "LevTreeView.h"
#include "LevSceneData.h"

using namespace Leviathan;

class LevSceneObjectTreeView : public LevTreeView
{
	Q_OBJECT

public:
	LevSceneObjectTreeView(QWidget* parent = nullptr);
	void SetSceneData(const Scene::LevSceneData& scene_data);

private:

};
