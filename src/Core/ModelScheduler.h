#pragma once

#include "LevScheduler.h"

namespace Leviathan
{
	class ModelScheduler : public LevScheduler<int>
	{
	public:
		ModelScheduler();
		void Update();
		void SetDone();

	private:
		bool m_done;
	};
}
