#pragma once

#include "LevScheduler.h"

namespace Leviathan
{
	class ModelScheduler : public LevScheduler<int>
	{
	public:
		UNIQUE_INSTANCE(ModelScheduler)

		ModelScheduler();
		void Update();
		void SetDone();

	private:
		bool m_done;
	};
}
