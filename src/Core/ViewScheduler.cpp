#include "ViewScheduler.h"
#include "RenderWindow.h"

namespace Leviathan
{
	ViewScheduler::ViewScheduler():
		m_done(false),
		 m_pView(nullptr)
	{
		auto _mainLoop = [this](CoPullType<int>& sink)
		{
			while (!m_done)
			{
				if (m_pView)
				{
					m_pView->Update();
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
		m_pView.reset(new View());
		EXIT_IF_FALSE(m_pView->Init(width, height, parentHandle));

		return true;
	}

	int ViewScheduler::GetWindowHandle()
	{
		return m_pView->GetWindowHandle();
	}

	bool ViewScheduler::LoadMeshFile(const char* file)
	{
		std::string path(file);

		AddTask([this, path](CoPullType<int>& sink)
			{
				m_pView->LoadMesh(path.c_str());
			});

		return true;
	}

	bool ViewScheduler::LoadPointCloudFile(const char * file)
	{
		std::string path(file);

		AddTask([this, path](CoPullType<int>& sink)
			{
				m_pView->LoadPointCloud(path.c_str());
			});

		return true;
	}
}
