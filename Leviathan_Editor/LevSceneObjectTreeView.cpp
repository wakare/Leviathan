#include "Node.h"
#include "LevSceneNode.h"
#include "LevSceneObjectTreeView.h"
#include "LevSceneObject.h"
#include "LevSceneData.h"
#include "LevSceneTree.h"
#include "LevSceneTreeTraverseVisitor.h"

LevSceneObjectTreeView::LevSceneObjectTreeView(QWidget* parent /*= nullptr*/)
	: LevTreeView(parent)
{

}

void LevSceneObjectTreeView::SetSceneData(const Scene::LevSceneData & scene_data)
{
	ClearCurrentItems();

	Scene::LevSceneTreeTraverseVisitor visitor;
	auto traverse_func = [this](const Scene::LevSceneObject& current_traverse_object, const std::vector<const Node<Scene::LevSceneObject>*>& traverse_stack)
	{
		QStandardItem* item = new QStandardItem;
		item->setText(QString(current_traverse_object.GetName().c_str()));
		AddListItem(item);

		return true;
	};

	visitor.SetTraverseCallback(traverse_func);

	auto root_node = &scene_data.GetSceneTree().GetRoot();
	const Node<Scene::LevSceneObject>* _node = dynamic_cast<const Node<Scene::LevSceneObject>*>(root_node);
	visitor.Apply(*_node);
}
