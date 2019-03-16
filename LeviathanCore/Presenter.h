#pragma once

#include <memory>

#include "LevStateControl.h"
#include "LevModelVisitor.h"

namespace Leviathan
{
	class Presenter
	{
	public:
		Presenter();

		LevStateControl& StateControl();
		LevModelVisitor& ModelVisitor();

	private:
		std::unique_ptr<LevStateControl> m_pStateControl;
		std::unique_ptr<LevModelVisitor> m_pModelVisitor;
	};

}
