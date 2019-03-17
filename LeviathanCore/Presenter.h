#pragma once

#include <memory>

#include "LevStateControl.h"
#include "LevModelVisitor.h"
#include "LevViewimpl.h"

namespace Leviathan
{
	class Presenter
	{
	public:
		Presenter();

		LevStateControl& StateControl();
		LevModelVisitor& ModelVisitor();
		LevViewImpl& ViewImpl();

	private:
		std::unique_ptr<LevStateControl> m_pStateControl;
		std::unique_ptr<LevModelVisitor> m_pModelVisitor;
		std::unique_ptr<LevViewImpl> m_pViewImpl;
	};

}
