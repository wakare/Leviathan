#pragma once

#include <memory>

#include "IDataCenter.h"

namespace Leviathan
{
	class LevModelVisitor
	{
	public:
		LevModelVisitor();
		const IDataCenter& DataCenter() const ;

	private:
		std::unique_ptr<IDataCenter> m_center;
	};
}