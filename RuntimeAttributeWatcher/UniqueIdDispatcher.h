#pragma once
#include <atomic>
#include <mutex>

namespace Util
{
	template <typename T>
	class UniqueIdDispatcher
	{
	public:
		static UniqueIdDispatcher& Instance();

		unsigned GetCurrentIdAndIncrement();

	private:
		UniqueIdDispatcher();

		static UniqueIdDispatcher* g_instance;
		std::atomic<unsigned> m_current_id;
	};

	template <typename T>
	UniqueIdDispatcher<T>& Util::UniqueIdDispatcher<T>::Instance()
	{
		if (!g_instance)
		{
			static std::once_flag _flag;
			std::call_once(_flag, []() { g_instance = new UniqueIdDispatcher<T>(); });
		}

		return *g_instance;
	}

	template <typename T>
	unsigned Util::UniqueIdDispatcher<T>::GetCurrentIdAndIncrement()
	{
		return m_current_id++;
	}

	template <typename T>
	inline Util::UniqueIdDispatcher<T>::UniqueIdDispatcher()
		: m_current_id(0)
	{

	}

}
