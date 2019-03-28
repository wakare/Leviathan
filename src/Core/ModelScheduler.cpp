#include "ModelScheduler.h"

namespace Leviathan
{
	ModelScheduler::ModelScheduler()
	{
		auto _mainLoop = [this](CoPullType<int>& sink)
		{
			while (!m_done)
			{
				LogLine("[MODEL_MAIN_LOOP] Tick!");
				sink();
			}

			LogLine("[MODEL_MAIN_LOOP] Exit!");
		};

		AddTask(_mainLoop);
	}

	void ModelScheduler::Update()
	{
		Tick();
	}

	void ModelScheduler::SetDone()
	{
		m_done = true;
	}

}