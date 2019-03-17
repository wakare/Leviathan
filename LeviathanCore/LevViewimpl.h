#pragma once
#include <memory>

#include "View.h"

namespace Leviathan
{
	class LevViewImpl
	{
	public:
		LevViewImpl();

	private:
		std::unique_ptr<View> m_pView;
	};
}