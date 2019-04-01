#pragma once

#include <memory>
#include "LevScheduler.h"
#include "Singleton.h"

namespace Leviathan
{
	class ModelScheduler;
	class ViewScheduler;
	class UserInterface;

	class PresenterScheduler : public LevScheduler<int>
	{
	public:
		DECLARE_SELF_TO_SINGLETON(PresenterScheduler)
		static PresenterScheduler& Instance();

		void Update();
		void SetDone();
		void SetState(AppState state);

		ModelScheduler& GetModelScheduler();
		ViewScheduler& GetViewScheduler();
		UserInterface& GetUserInterface();
		const AppState& GetAppState() const;  

	private:
		PresenterScheduler();

		AppState m_state;
		bool m_done;

		std::shared_ptr<ModelScheduler> m_pModelScheduler;
		std::shared_ptr<ViewScheduler> m_pViewScheduler;
		std::shared_ptr<UserInterface> m_pUserInterface;
	};
}