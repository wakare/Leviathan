#include "LevResourcesListView.h"
#include "NodeVisitor.h"
#include "GlobalDef.h"
#include "LevFileSystem.h"

class FileNodeVisitor : public NodeVisitor<LevFileDesc>
{
public:
	FileNodeVisitor(LevResourcesListView& view);

	virtual void Apply(Node<LevFileDesc>& node);
	virtual void Apply(const Node<LevFileDesc>& node);

private:
	void ApplyImpl(const Node<LevFileDesc>& node);

	LevResourcesListView& m_view;
};

FileNodeVisitor::FileNodeVisitor(LevResourcesListView& view)
	: m_view(view)
{
}

void FileNodeVisitor::Apply(Node<LevFileDesc>& node)
{
	ApplyImpl(node);
}

void FileNodeVisitor::Apply(const Node<LevFileDesc>& node)
{
	ApplyImpl(node);
}

void FileNodeVisitor::ApplyImpl(const Node<LevFileDesc>& node)
{
	// Clear all items
	m_view.ClearItems();

	bool is_root_file = !node.GetParent().Get();

	if (!is_root_file)
	{
		auto& parent_node = node.GetParent();

		QIcon icon = m_view.style()->standardIcon(QStyle::SP_DirIcon);
		QStandardItem* item = new QStandardItem(icon, QString("File"));

		FileNodeType* node_data = new FileNodeType;
		node_data->SetData(parent_node.Get());

		item->setData(QVariant::fromValue(node_data));
		item->setText(QString(".."));
		m_view.AddItem(item);
	}

	for (auto& child : node.GetChildren())
	{
		auto& data = child->GetNodeData();
		// std::cout << ((data->type == LevFileType::EFT_DIR_FILE) ? "Directory: " : "Regular: ") << data->file_name << std::endl;

		QIcon icon = m_view.style()->standardIcon((data->type == EFT_REGULAR_FILE) ? QStyle::SP_FileIcon : QStyle::SP_DirIcon);
		QStandardItem* item = new QStandardItem(icon, QString("File"));

		FileNodeType* node_data = new FileNodeType;
		node_data->SetData(child.Get());

		item->setData(QVariant::fromValue(node_data));
		item->setText(QString(data->file_name.c_str()));
		m_view.AddItem(item);
	}
}

LevResourcesListView::LevResourcesListView(QWidget* parent /*= nullptr*/)
	: LevListView(parent)
	, m_file_system_root_node(nullptr)
{
	connect(this, SIGNAL(doubleClicked(const QModelIndex &)), this, SLOT(ListViewClicked(const QModelIndex &)));

	setAcceptDrops(true);
	//setDragDropMode(QAbstractItemView::InternalMove);
	setDragDropMode(QAbstractItemView::DragDrop);
	setSelectionMode(QAbstractItemView::SingleSelection);
}

bool LevResourcesListView::SetResourcesFolderPath(const char* path)
{
	EXIT_IF_FALSE( LevFileSystem::LoadDirectory(path, m_file_system_root_node));
	LEV_ASSERT(m_file_system_root_node.Get());

	return true;
}

bool LevResourcesListView::InitItemsFormNode(const Node<LevFileDesc>& node)
{
	FileNodeVisitor item_init_visitor(*this);
	item_init_visitor.Apply(node);

	return true;
}

const LevFileNode& LevResourcesListView::GetRootNode() const
{
	return *m_file_system_root_node;
}

void LevResourcesListView::ListViewClicked(const QModelIndex & index)
{
	// Qt::UserRole + 1 is hard code, should be more elegant
	FileNodeType* node_data = index.data(Qt::UserRole + 1).value<FileNodeType*>();
	if (!node_data)
	{
		return;
	}

	switch (node_data->GetData()->GetNodeData()->type)
	{
	case Leviathan::EFT_DIR_FILE:
		_folderClicked(*node_data->GetData());
		break;

	case Leviathan::EFT_REGULAR_FILE:
		_regularFileClicked(*node_data->GetData());
		break;

	default:
		break;
	}
}

void LevResourcesListView::_folderClicked(const Node<LevFileDesc>& node)
{
	InitItemsFormNode(node);
}

void LevResourcesListView::_regularFileClicked(const Node<LevFileDesc>& node)
{
	// Do nothing
}

FileNodeType::FileNodeType()
{

}

void FileNodeType::SetData(const Node<LevFileDesc>* data)
{
	m_data = data;
}

const Leviathan::Node<LevFileDesc>* FileNodeType::GetData() const
{
	return m_data;
}
