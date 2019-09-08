#pragma once

#include <QStandardItem>
#include "LSPtr.h"
#include "LevFileSystem.h"
#include "Node.h"
/*
	User-defined data type for storing it to QStandardItem
*/

class FileNodeType
{
public:
	FileNodeType();

	void SetData(const Node<LevFileDesc>* data);
	const Node<LevFileDesc>* GetData() const;

private:
	const Node<LevFileDesc>* m_data;
};

Q_DECLARE_METATYPE(FileNodeType*);

template <typename T>
class LevStandardItem : public QStandardItem
{
	Q_OBJECT

public:
	LevStandardItem();

private:
	
};