#pragma once
#include <memory>

#include "View.h"

namespace Leviathan
{
	class Presenter;

	class LevViewImpl
	{
	public:
		LevViewImpl(Presenter& presenter);

	private:
		Presenter& m_presenter;
		std::unique_ptr<View> m_pView;
	};
}