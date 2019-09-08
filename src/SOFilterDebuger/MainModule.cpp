#include "MainModule.h"
#include "LevCoroutine.h"
#include "CommandCenter.h"
#include "DataUpdateCommand.h"
#include "RenderCommand.h"
#include "SOFDataCenter.h"
#include "LevSceneNode.h"
#include "DebugModule.h"

namespace SOFilter
{
	MainModule::MainModule()
		: m_parameter(nullptr)
		, m_inited(false)
		, m_exited(false)
		, m_need_updated(false)
		, m_command_center(new CommandCenter)
		, m_debug_module(new DebugModule)
	{
		
	}

	bool MainModule::SetupConfig(const MainModuleParameters & parameters)
	{
		m_parameter.Reset(new MainModuleParameters(parameters));
		EXIT_IF_FALSE(m_parameter);

		// Init & run render thread
		EXIT_IF_FALSE(_runRenderThread(*m_parameter));

		DataUpdateCommandParameter parameter;
		parameter.data_folder = m_parameter->data_folder;
		parameter.data_format = m_parameter->data_file_format;
		parameter.start_index = m_parameter->data_start_index;
		parameter.end_index = m_parameter->data_end_index;

 		LSPtr<DataUpdateCommand> update_command = new DataUpdateCommand(parameter);
 		m_command_center->PostCommand(TryCast<DataUpdateCommand, Command>(update_command));

		// Init task
		auto _mainModuleLogic = [this](CoPullType<int>& sink)
		{
			LogLine("[DEBUG] Enter main module logic loop.");

			while (!m_exited)
			{
				m_command_center->DoCommands();
				sink();
			}

			LogLine("[DEBUG] Exit main module logic loop.");
		};

		DoAsyncTask(_mainModuleLogic);
		
		return true;
	}

	void MainModule::SetExit()
	{
		m_exited = true;
		LevRuntimeInterface::Stop();
	}

	void MainModule::SetNeedUpdate()
	{
		m_need_updated = true;
	}

	void MainModule::PushRequest(MainModuleRequest request)
	{
		std::lock_guard<std::mutex> lock(m_request_lock);
		m_main_module_requests.push_back(request);
	}

	void MainModule::DebugStart()
	{
		m_debug_module->DebugStart();
	}

	void MainModule::DebugStop()
	{
		m_debug_module->DebugStop();
	}

	void MainModule::DebugTick()
	{
		m_debug_module->DebugTick();
	}

	void MainModule::DebugRollback()
	{
		m_debug_module->DebugRollback();
	}

	void MainModule::Update()
	{
		if (!m_need_updated)
		{
			return;
		}

		if (!m_inited)
		{
			return;
		}

		m_debug_module->Update();

		_handleRequest();
		_tick();
		
		static bool _first = true;

		if (_first)
		{
			_firstUpdate();
			_first = false;
		}
	}

	bool MainModule::_runRenderThread(const MainModuleParameters & parameter)
	{
		m_render_thread = std::thread([this]()
			{
				// Attach render device context
				LevRuntimeInterface::Init(m_parameter->window_width, m_parameter->window_height, m_parameter->window_handle);
				m_inited = true;

				// Do loop
				while (true)
				{
					LevRuntimeInterface::Update();
				}
			}
		);

		m_render_thread.detach();

		return true;
	}
	void MainModule::_renderPointCloud()
	{
		// Post render command
		auto _render_command = [this]()
		{
			unsigned out_index = 0;
			LSPtr<PointCloudf> point_cloud = SOFDataCenter::Instance().GetOnePointCloud(out_index);
			EXIT_IF_FALSE(point_cloud);
			LSPtr<Scene::LevSceneNode> out_node = nullptr;
			LevRuntimeInterface::LoadPointCloud(*point_cloud, out_node);

			return true;
		};

		auto _render_task = [this, _render_command](CoPullType<int>& sink)
		{
			for (unsigned i = m_parameter->data_start_index; i < m_parameter->data_end_index; i++)
			{
				LSPtr<RenderCommand> render_command = new RenderCommand(_render_command, nullptr);
				m_command_center->PostCommand(TryCast<RenderCommand, Command>(render_command));

				Sleep(100);
				sink();
			}
		};

		DoAsyncTask(_render_task);
	}

	void MainModule::_firstUpdate()
	{
		_renderPointCloud();
	}

	void MainModule::_handleRequest()
	{
		for (auto& request : m_main_module_requests)
		{
			request();
		}
	}
}