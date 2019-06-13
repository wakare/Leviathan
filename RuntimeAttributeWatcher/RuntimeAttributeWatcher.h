#pragma once

#include <map>
#include <memory>

#include "RuntimeAttribute.h"

namespace Util
{
	class RuntimeAttributeWatcher
	{
	public:
		RuntimeAttributeWatcher();
		RuntimeAttributeWatcher(const RuntimeAttributeWatcher& lhs) = delete;
		RuntimeAttributeWatcher(const RuntimeAttributeWatcher&& lhs) = delete;

		bool Register(std::unique_ptr<RuntimeAttribute> attribute);
		bool Unregister(unsigned id);

	private:
		std::map<unsigned, std::unique_ptr<RuntimeAttribute>> m_attributes;
	};
}