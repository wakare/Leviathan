#pragma once
#include "LevListView.h"
#include "LevSceneData.h"

using namespace Leviathan;

class LevSceneObjectListView : public LevListView
{
	Q_OBJECT

public:
	LevSceneObjectListView(QWidget* parent = nullptr);
	void SetSceneData(const Scene::LevSceneData& scene_data);

private:

};