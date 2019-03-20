#pragma once
#include <memory>
#include "Singleton.h"

namespace PGCT
{
	template <typename T>
	class IFactoryInputAttribute
	{
		virtual void StubMethod() = 0;
	};

	template <typename T>
	class SimpleFactory
	{
	public:
		virtual std::unique_ptr<T> Create(IFactoryInputAttribute<T>& input) = 0;
	};
}