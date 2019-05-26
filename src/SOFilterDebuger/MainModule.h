#pragma once
#include "LevScheduler.h"
#include "LevRuntimeInterface.h"

using namespace Leviathan;

namespace Leviathan
{
	class CommandCenter;
}

namespace SOFilter
{
	class DebugModule;

	struct MainModuleParameters
	{
		// 1.0 represent do one frame Soft-organization filter.
		float tick_speed;

		std::string data_folder;
		std::string data_file_format;
		unsigned data_start_index;
		unsigned data_end_index;

		unsigned window_handle;
		unsigned window_width;
		unsigned window_height;
	};

	typedef std::function<void()> MainModuleRequest;

	class MainModule : public LevScheduler<int>
	{
	public:
		/*
			Environment install interface.
		*/
		MainModule();
		bool SetupConfig(const MainModuleParameters& parameters);
		void SetExit();
		void SetNeedUpdate();
		void PushRequest(MainModuleRequest request);

		/*
			Debug feature interface.
		*/
		void DebugStart();
		void DebugStop();
		void DebugTick();
		void DebugRollback();

		/* 
			Update should be called once a frame.
		*/
		void Update();

	private:
		bool _runRenderThread(const MainModuleParameters& parameter);
		void _renderPointCloud();
		void _firstUpdate();
		void _handleRequest();

		volatile bool m_inited;
		volatile bool m_need_updated;
		bool m_exited;

		std::thread m_render_thread;

		std::mutex m_request_lock;
		std::vector<MainModuleRequest> m_main_module_requests;

		LPtr<MainModuleParameters> m_parameter;
		LPtr<CommandCenter> m_command_center;
		LPtr<DebugModule> m_debug_module;
	};
}