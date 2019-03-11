#pragma once
#include <mutex>

	template <typename T>
	class Singleton
	{
	public:
		static T& Instance()
		{
			if (!g_pInstance)
			{
				static std::once_flag flag;
				std::call_once(flag, []() {g_pInstance = new T(); });
			}
			return 	*g_pInstance;
		}

	protected:
		Singleton<T>() = delete;
		Singleton<T>(const Singleton<T>&) = delete;
		Singleton<T>(const Singleton<T>&&) = delete;
		Singleton<T> operator=(const Singleton<T>& rhs) = delete;
		Singleton<T> operator=(const Singleton<T>&& rhs) = delete;

		static T* g_pInstance;
	};

	template<typename T>
	T* Singleton<T>::g_pInstance = nullptr;

#define DECLARE_SELF_TO_SINGLETON(className) friend class Singleton<className>;