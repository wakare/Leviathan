#pragma once

#include "LevScheduler.h"

namespace Leviathan
{
	class ModelScheduler : public LevScheduler<int>
	{
	public:
		ModelScheduler();
		void Update();
	};
}
