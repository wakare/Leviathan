#pragma once

#include <boost/coroutine2/all.hpp>
#include <boost/coroutine2/detail/push_coroutine.hpp>
#include <boost/coroutine2/detail/pull_coroutine.hpp>

namespace Leviathan
{

#define BOOST_CO_PUSH(type) boost::coroutines2::coroutine<type>::push_type
#define BOOST_CO_PULL(type) boost::coroutines2::coroutine<type>::pull_type

	template<class T>
	class LevCoroutine
	{
	public:
		LevCoroutine(std::function<void(BOOST_CO_PULL(T)&)> func);
		void Tick(T t);
		bool Valid() const;

	private:
		BOOST_CO_PUSH(T) m_caller;
	};
}

#include "LevCoroutine.hpp"