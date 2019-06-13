#pragma once

#include <map>
#include <memory>

#include "RuntimeAttribute.h"

namespace Util
{
	typedef std::function<void(RuntimeAttribute&)> AttributeMatched;
	typedef std::function<void(RuntimeAttribute&)> AttributeSearched;

	class RuntimeAttributeWatcher
	{
	public:
		RuntimeAttributeWatcher();
		RuntimeAttributeWatcher(const RuntimeAttributeWatcher& lhs) = delete;
		RuntimeAttributeWatcher(const RuntimeAttributeWatcher&& lhs) = delete;

		bool Register(std::unique_ptr<RuntimeAttribute> attribute);
		bool Unregister(unsigned id);

		bool MatchOne(const INTERN_STRING& key, AttributeMatched updater);
		bool SearchAll(const INTERN_STRING& key, AttributeSearched updater);

	private:
		std::map<unsigned, std::unique_ptr<RuntimeAttribute>> m_attributes;
	};
}