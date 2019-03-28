#include "PresenterScheduler.h"

namespace Leviathan
{
	PresenterScheduler::PresenterScheduler():
		m_done(false),
		m_pModelScheduler(new ModelScheduler),
		m_pViewScheduler(new ViewScheduler)
	{
		// Presenter main loop coroutine
		auto _mainLoop = [this](CoPullType<int>& sink)
		{
			while (!m_done)
			{
				LogLine("[PRESENTER_MAIN_LOOP] Tick!");
				sink();
			}

			LogLine("[PRESENTER_MAIN_LOOP] Exit!");
		};

		AddTask(_mainLoop);
	}

	PresenterScheduler & PresenterScheduler::Instance()
	{
		return Singleton<PresenterScheduler>::Instance();
	}

	void PresenterScheduler::Update()
	{
		m_pModelScheduler->Update();
		Tick();
	}

	void PresenterScheduler::SetDone()
	{
		m_pModelScheduler->SetDone();
		m_pViewScheduler->SetDone();
		m_done = true;
	}

	ModelScheduler & PresenterScheduler::GetModelScheduler()
	{
		return *m_pModelScheduler;
	}

	ViewScheduler & PresenterScheduler::GetViewScheduler()
	{
		return *m_pViewScheduler;
	}
}