#pragma once
#include <memory>
#include <QListView>
#include <QScopedPointer>
#include <QStandardItemModel>

class LevListView : public QListView
{
	Q_OBJECT

public:
	LevListView(QWidget* parent = nullptr);
	void ClearItems();
	void AddItem(std::unique_ptr<QStandardItem> item);

private:
	bool _initStandardModel();
	bool _initListView();

	QScopedPointer<QStandardItemModel> m_standard_model;
	std::vector<std::unique_ptr<QStandardItem>> m_items;
};
