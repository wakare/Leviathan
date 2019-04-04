#pragma once

#include <boost/coroutine2/all.hpp>
#include <boost/coroutine2/detail/push_coroutine.hpp>
#include <boost/coroutine2/detail/pull_coroutine.hpp>
#include <functional>

namespace Leviathan
{
	template <typename T>
	using CoPullType = boost::coroutines2::detail::pull_coroutine<T>;

	template <typename T>
	using CoPushType = boost::coroutines2::detail::push_coroutine<T>;

	template<typename T>
	class LevCoroutine
	{
	public:
		LevCoroutine(std::function<void(CoPullType<typename T>&)> func);
		void Tick(T t);
		bool Valid() const;

	private:
		CoPushType<typename T> m_caller;
	};
}

#include "LevCoroutine.hpp"