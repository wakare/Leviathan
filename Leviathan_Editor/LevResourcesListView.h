#pragma once

#include <LevListView.h>
#include "LPtr.h"
#include "LevFileSystem.h"
#include "Node.h"

/*
	User-defined data type for storing it to QStandardItem
*/

class FileNodeType
{
public:
	FileNodeType()
	{

	}

	void SetData(const Node<LevFileDesc>* data)
	{
		m_data = data;
	}

	const Node<LevFileDesc>* GetData() const
	{
		return m_data;
	}

private:
	const Node<LevFileDesc>* m_data;
};

Q_DECLARE_METATYPE(FileNodeType*);

class LevResourcesListView : public LevListView
{
	Q_OBJECT

public:
	LevResourcesListView(QWidget* parent = nullptr);
	bool SetResourcesFolderPath(const char* path);
	bool InitItemsFormNode(const Node<LevFileDesc>& node);
	const LevFileNode& GetRootNode() const;

public slots:
	void ListViewClicked(const QModelIndex & index);

private:
	LPtr<LevFileNode> m_file_system_root_node;
};