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
	void ClearItems();
	void AddItem(QStandardItem* item);

protected:
	bool _initStandardModel();
	bool _initTreeView();

	QScopedPointer<QStandardItemModel> m_standard_model;
};
