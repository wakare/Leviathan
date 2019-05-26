#pragma once

#include <thread>

namespace Leviathan
{
	/*
		ThreadRecorder is a tool class for recording thread_info when derived class created.
	*/

	class ThreadRecorder
	{
	public:
		ThreadRecorder();
		bool IsCreateThread();

		virtual ~ThreadRecorder() = default;

	private:
		std::thread::id m_tid;
	};
}