#pragma once
#include <memory>
#include <map>

namespace Leviathan
{
	typedef unsigned DataHandle;

	template <typename T>
	class DataStorer
	{
	public:
		DataStorer();
		bool Store(std::unique_ptr<T> obj);

		T& Get(DataHandle handle);
		const T& Get(DataHandle handle) const;

	private:
		std::map<DataHandle, std::unique_ptr<T>> m_data;
	};

	#include "DataStorer.hpp"
	
	#define LevDataStorer DataStorer<IResource>
}