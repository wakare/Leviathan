#include <QStandardItemModel>
#include "Node.h"
#include "LevSceneNode.h"
#include "LevSceneObjectTreeView.h"
#include "LevSceneObject.h"
#include "LevSceneData.h"
#include "LevSceneTree.h"
#include "LevSceneTreeTraverseVisitor.h"

LevSceneObjectTreeView::LevSceneObjectTreeView(QWidget* parent /*= nullptr*/)
	: LevTreeView(parent)
	, m_need_update_list(false)
{

}

void LevSceneObjectTreeView::SetSceneData(const Scene::LevSceneData & scene_data)
{
	std::lock_guard<std::mutex> lock(m_next_update_items_lock);

	for (auto item : m_next_update_items)
	{
		delete item;
	}

	m_next_update_items.clear();
	m_need_update_list = true;

	Scene::LevSceneTreeTraverseVisitor visitor;
	
	auto traverse_func = [this](const Scene::LevSceneObject& current_traverse_object, const std::vector<const Node<Scene::LevSceneObject>*>& traverse_stack)
	{
		// TODO: use other safe point to hold item resource
		QStandardItem* item = new QStandardItem;
		item->setText(QString(current_traverse_object.GetName().c_str()));
		m_next_update_items.push_back(item);

		return true;
	};

	visitor.SetTraverseCallback(traverse_func);

	auto root_node = &scene_data.GetSceneTree().GetRoot();
	const Node<Scene::LevSceneObject>* _node = dynamic_cast<const Node<Scene::LevSceneObject>*>(root_node);
	visitor.Apply(*_node);
}

void LevSceneObjectTreeView::Update()
{
	if (!m_need_update_list)
	{
		return;
	}
	
	std::lock_guard<std::mutex> lock(m_next_update_items_lock);
	m_need_update_list = false;
	ClearItems();

	for (auto* item : m_next_update_items)
	{
		LEV_ASSERT(item);
		AddItem(item);
	}

	m_next_update_items.clear();
}
