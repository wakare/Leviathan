#pragma once
#include <atomic>
#include "GlobalDef.h"

namespace Leviathan
{
	/*
		This class is used for generate increment token with thread-safe interface.
		Only support base type argument.
	*/

	template <typename class_type, typename scalar>
	class LevTokenDispatch
	{
	public:
		UNIQUE_INSTANCE(LevTokenDispatch)
		static scalar GetToken();

	private:
		LevTokenDispatch() = delete;
		static std::atomic<scalar> m_token_seed;
	};

	template<typename class_type, typename scalar>
	inline scalar LevTokenDispatch<class_type, scalar>::GetToken()
	{
		return m_token_seed++;
	}

	template <typename class_type, typename scalar>
	std::atomic<scalar> LevTokenDispatch<class_type, scalar>::m_token_seed;
}
