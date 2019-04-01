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
				if (m_pViewData) 
				{
					auto pScene = m_pViewData->GetRenderWindow().GetScene();
					if (pScene)
					{
						pScene->Update();
					}
				}

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
		EXIT_IF_FALSE(m_pViewData->GetRenderWindow().CreateRenderWindow(width, height, parentHandle));
		return true;
	}

	int ViewScheduler::GetWindowHandle()
	{
		return m_pViewData->GetRenderWindow().GetWindowHandle();
	}

}
