#pragma once
#include <memory>
#include <QListView>
#include <QScopedPointer>
#include <QStandardItemModel>

class LevListView : public QListView
{
public:
	LevListView(QWidget* parent = nullptr);
	void ClearCurrentItems();
	void AddListItem(std::unique_ptr<QStandardItem> item);

private:
	bool _initStandardModel();
	bool _initListView();

	QScopedPointer<QStandardItemModel> m_standard_model;
	std::vector<std::unique_ptr<QStandardItem>> m_items;
};
