#pragma once
#include <QGroupBox>

class LevAttributeWidget : public QGroupBox
{
public:
	LevAttributeWidget(QWidget* parent = nullptr);
	void SetViewSize(unsigned width, unsigned height);
	
private:
	void _setupAttributeView();
};


