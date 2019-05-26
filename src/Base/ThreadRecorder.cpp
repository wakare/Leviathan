#include "ThreadRecorder.h"

namespace Leviathan
{
	ThreadRecorder::ThreadRecorder()
		: m_tid(std::this_thread::get_id())
	{
	}

	bool ThreadRecorder::IsCreateThread()
	{
		return std::this_thread::get_id() == m_tid;
	}

}

