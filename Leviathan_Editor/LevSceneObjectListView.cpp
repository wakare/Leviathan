#include "LevSceneObjectListView.h"
#include "LevSceneTreeTraverseVisitor.h"
#include "LevSceneTree.h"
#include "LevSceneData.h"
#include "LevSceneObject.h"
#include "LevSceneNode.h"
#include "Node.h"

LevSceneObjectListView::LevSceneObjectListView(QWidget* parent)
	: LevListView(parent)
{

}


void LevSceneObjectListView::SetSceneData(const Scene::LevSceneData& scene_data)
{
	ClearCurrentItems();

	Scene::LevSceneTreeTraverseVisitor visitor;
	auto traverse_func = [this](const Scene::LevSceneObject& current_traverse_object, const std::vector<const Node<Scene::LevSceneObject>*>& traverse_stack)
	{
		std::unique_ptr<QStandardItem> item;
		item.reset(new QStandardItem);

		char desc_buf[100];
		snprintf(desc_buf, sizeof(desc_buf), "Scene object: %u", current_traverse_object.GetID());

		item->setText(QString(desc_buf));
		AddListItem(std::move(item));

		return true;
	};

	visitor.SetTraverseCallback(traverse_func);

	auto root_node = &scene_data.GetSceneTree().GetRoot();
	const Node<Scene::LevSceneObject>* _node = dynamic_cast<const Node<Scene::LevSceneObject>*>(root_node);
	visitor.Apply(*_node);
}
