#include "LevModelVisitor.h"
#include "DataCenterImpl.h"

namespace Leviathan
{
	LevModelVisitor::LevModelVisitor():
		m_center(new DataCenterImpl)
	{

	}

	const IDataCenter & LevModelVisitor::DataCenter() const
	{
		return *m_center;
	}
}