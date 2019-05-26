#pragma once

#include <memory>
#include "LevScheduler.h"
#include "Singleton.h"

namespace Leviathan
{
	class ModelScheduler;
	class ViewScheduler;
	class LevRuntimeInterface;
	class ToolModule;

	class PresenterScheduler : public LevScheduler<int>
	{
	public:
		UNIQUE_INSTANCE(PresenterScheduler)
		DECLARE_SELF_TO_SINGLETON(PresenterScheduler)
		static PresenterScheduler& Instance();

		void Update();
		void SetDone();
		void SetState(AppState state);

		ModelScheduler& GetModelScheduler();
		ViewScheduler& GetViewScheduler();
		LevRuntimeInterface& GetUserInterface();
		ToolModule& GetToolModule();
		const AppState& GetAppState() const;  

	private:
		PresenterScheduler();

		AppState m_state;
		bool m_done;

		LPtr<ModelScheduler> m_pModelScheduler;
		LPtr<ViewScheduler> m_pViewScheduler;
		LPtr<LevRuntimeInterface> m_pUserInterface;
		LPtr<ToolModule> m_pToolModule;
	};
}