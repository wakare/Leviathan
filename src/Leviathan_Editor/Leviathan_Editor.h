#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Leviathan_Editor.h"
#include <QScopedPointer>
#include <QOpenGLWidget>
#include <QSplitter>
#include <QTimer>
#include "LevListView.h"
#include "LevTreeView.h"
#include "LevAttributeWidget.h"
#include "LeviathanProxy.h"
#include "LevSceneObjectTreeView.h"
#include "LevResourcesListView.h"

class Leviathan_Editor : public QMainWindow
{
	Q_OBJECT

public:
	Leviathan_Editor(QWidget *parent = Q_NULLPTR);

public slots:
	void SLOT_RESIZE();
	void SLOT_UPDATE();

protected:
	virtual void resizeEvent(QResizeEvent *event);
	virtual void closeEvent(QCloseEvent *event);

private:
	void _widget_initialized();
	void _leviathan_initialized();
	void _update_runtime_scene_object();
	void _attachRenderer();

	bool _setupWidget();
	bool _setupResourceListView();
	bool _setupSceneRuntimeObjectView();
	bool _setupAttributePanelView();

	Ui::Leviathan_EditorClass ui;

	QScopedPointer<QSplitter> m_main_splitter;
	QScopedPointer<QSplitter> m_middle_splitter;
	QScopedPointer<QSplitter> m_sub_splitter;

	QScopedPointer<QOpenGLWidget> m_openGL_widget;
	QScopedPointer<LevSceneObjectTreeView> m_runtime_object_view;
	QScopedPointer<LevResourcesListView> m_resource_view;
	QScopedPointer<LevAttributeWidget> m_attribute_view;

	QScopedPointer<QTimer> m_timer;
	LSPtr<LeviathanProxy> m_leviathan_proxy;
};
