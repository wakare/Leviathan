#pragma once

#include "LevScheduler.h"
#include "TriDScene.h"
#include "ViewData.h"

namespace Leviathan 
{
	class ViewScheduler : public LevScheduler<int>
	{
	public:
		ViewScheduler();
		void Update();
		void SetDone();

		bool Init(int width, int height, int parentHandle);

		int GetWindowHandle();

	private:

		bool m_done;
		std::unique_ptr<ViewData> m_pViewData;
	};
}