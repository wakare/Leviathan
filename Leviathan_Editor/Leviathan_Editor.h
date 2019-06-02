#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Leviathan_Editor.h"
#include <QScopedPointer>
#include <QOpenGLWidget>
#include <QSplitter>
#include "LevListView.h"
#include "LevAttributeWidget.h"

class Leviathan_Editor : public QMainWindow
{
	Q_OBJECT

public:
	Leviathan_Editor(QWidget *parent = Q_NULLPTR);

private:
	void _setupWidget();

	Ui::Leviathan_EditorClass ui;

	QScopedPointer<QSplitter> m_main_splitter;
	QScopedPointer<QSplitter> m_middle_splitter;
	QScopedPointer<QSplitter> m_sub_splitter;

	QScopedPointer<QOpenGLWidget> m_openGL_widget;
	QScopedPointer<LevListView> m_runtime_object_list_view;
	QScopedPointer<LevListView> m_resource_list_view;
	QScopedPointer<LevAttributeWidget> m_attribute_view;
};
