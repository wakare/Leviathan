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
	void AddItem(QStandardItem* item);

protected:
	bool _initStandardModel();
	bool _initListView();

	QScopedPointer<QStandardItemModel> m_standard_model;
};
