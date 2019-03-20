#pragma once

#include <memory>

#include "LevStateControl.h"
#include "LevModelVisitor.h"
#include "LevViewimpl.h"
#include "Singleton.h"

namespace Leviathan
{
	class Presenter
	{
		DECLARE_SELF_TO_SINGLETON(Presenter)

	public:
		static Presenter& Instance();

		LevStateControl& StateControl();
		LevModelVisitor& ModelVisitor();
		LevViewImpl& ViewImpl();

	private:
		Presenter();

		std::unique_ptr<LevStateControl> m_pStateControl;
		std::unique_ptr<LevModelVisitor> m_pModelVisitor;
		std::unique_ptr<LevViewImpl> m_pViewImpl;
	};
}
