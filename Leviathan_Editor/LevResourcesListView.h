#pragma once

#include <LevListView.h>

class LevResourcesListView : public LevListView
{
	Q_OBJECT

public:
	LevResourcesListView(QWidget* parent = nullptr);
	void SetResourcesFolderPath(const char* path);

private:

};