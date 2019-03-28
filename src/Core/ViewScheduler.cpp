#include "ViewScheduler.h"
#include "RenderWindow.h"

namespace Leviathan
{
	ViewScheduler::ViewScheduler():
		m_done(false),
		m_pViewData(nullptr)
	{
		auto _mainLoop = [this](CoPullType<int>& sink)
		{
			while (!m_done)
			{
				LogLine("[VIEW_MAIN_LOOP] Tick!");
				sink();
			}

			LogLine("[VIEW_MAIN_LOOP] Exit!");
		};

		AddTask(_mainLoop);
	}

	void ViewScheduler::Update()
	{
		Tick();
	}

	void ViewScheduler::SetDone()
	{
		m_done = true;
	}

	bool ViewScheduler::Init(int width, int height, int parentHandle)
	{
		m_pViewData.reset(new ViewData(IScene::EST_TRID));
		return m_pViewData->GetRenderWindow().CreateRenderWindow(width, height, parentHandle);
	}

}
