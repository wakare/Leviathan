#pragma once
#include <QListView>
#include <QScopedPointer>
#include <QStandardItemModel>

class LevListView : public QListView
{
public:
	LevListView(QWidget* parent = nullptr);


private:
	bool _initStandardModel();
	bool _initListView();

	QScopedPointer<QStandardItemModel> m_standard_model;
};
