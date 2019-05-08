#include "PresenterScheduler.h"

#include "ModelScheduler.h"
#include "ViewScheduler.h"
#include "UserInterface.h"
#include "ToolModule.h"

namespace Leviathan
{
	PresenterScheduler::PresenterScheduler():
		m_done(false),
		m_pModelScheduler(new ModelScheduler),
		m_pViewScheduler(new ViewScheduler),
		m_pUserInterface(new UserInterface),
		m_pToolModule(new ToolModule)
	{
		// Presenter main loop coroutine
		auto _mainLoop = [this](CoPullType<int>& sink)
		{
			while (!m_done)
			{
				sink();
			}

			LogLine("[PRESENTER_MAIN_LOOP] Exit!");
		};

		DoTask(_mainLoop);
	}

	PresenterScheduler & PresenterScheduler::Instance()
	{
		return Singleton<PresenterScheduler>::Instance();
	}

	void PresenterScheduler::Update()
	{
		m_pModelScheduler->Update();
		m_pViewScheduler->Update();
		_tick();
	}

	void PresenterScheduler::SetDone()
	{
		m_pModelScheduler->SetDone();
		m_pViewScheduler->SetDone();
		m_done = true;
	}

	void PresenterScheduler::SetState(AppState state)
	{
		m_state = state;
	}

	ModelScheduler & PresenterScheduler::GetModelScheduler()
	{
		return *m_pModelScheduler;
	}

	ViewScheduler & PresenterScheduler::GetViewScheduler()
	{
		return *m_pViewScheduler;
	}

	Leviathan::UserInterface& PresenterScheduler::GetUserInterface()
	{
		return *m_pUserInterface;
	}

	ToolModule & PresenterScheduler::GetToolModule()
	{
		return *m_pToolModule;
	}

	const AppState& PresenterScheduler::GetAppState() const
	{
		return m_state;
	}

}