#include "ModelScheduler.h"
#include "RenderService.h"

namespace Leviathan
{
	ModelScheduler::ModelScheduler()
	{
		auto _mainLoop = [this](CoPullType<int>& sink)
		{
			while (!m_done)
			{
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