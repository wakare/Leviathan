#pragma once
#include <mutex>
#include "LevTreeView.h"
#include "LevSceneData.h"

using namespace Leviathan;

class LevSceneObjectTreeView : public LevTreeView
{
	Q_OBJECT

public:
	LevSceneObjectTreeView(QWidget* parent = nullptr);
	void SetSceneData(const Scene::LevSceneData& scene_data);
	void Update();

private:
	bool m_need_update_list;
	std::mutex m_next_update_items_lock;
	std::vector<QStandardItem*> m_next_update_items;
};
