#pragma once
#include <memory>
#include <QTreeView>
#include <QStandardItemModel>
#include <QScopedPointer>

class LevTreeView : public QTreeView
{
	Q_OBJECT

public:
	LevTreeView(QWidget* parent = nullptr);
	void ClearCurrentItems();
	void AddListItem(QStandardItem* item);

private:
	bool _initStandardModel();
	bool _initTreeView();

	QScopedPointer<QStandardItemModel> m_standard_model;
};
