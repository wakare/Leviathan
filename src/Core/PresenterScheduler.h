#pragma once

#include <memory>
#include "LevScheduler.h"
#include "ModelScheduler.h"
#include "ViewScheduler.h"
#include "Singleton.h"

enum AppState
{
	EAS_UNINITED,
	EAS_INITING,
	EAS_INITED,
	EAS_RUNNING,
	EAS_STOPPING,
	EAS_STOPPED
};

namespace Leviathan
{
	class PresenterScheduler : public LevScheduler<int>
	{
	public:
		DECLARE_SELF_TO_SINGLETON(PresenterScheduler)
		static PresenterScheduler& Instance();

		void Update();
		void SetDone();

		ModelScheduler& GetModelScheduler();
		ViewScheduler& GetViewScheduler();

	private:
		PresenterScheduler();

		AppState m_state;
		bool m_done;

		std::unique_ptr<ModelScheduler> m_pModelScheduler;
		std::unique_ptr<ViewScheduler> m_pViewScheduler;
	};
}