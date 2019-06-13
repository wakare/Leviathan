#include "RuntimeAttributeWatcher.h"
#include "StringMatcher.h"

namespace Util
{
	RuntimeAttributeWatcher::RuntimeAttributeWatcher()
	{

	}

	bool RuntimeAttributeWatcher::Register(std::unique_ptr<RuntimeAttribute> attribute)
	{
		auto it = m_attributes.find(attribute->GetId());
		if (it != m_attributes.end())
		{
			return false;
		}

		m_attributes[attribute->GetId()] = std::move(attribute);
		return true;
	}

	bool RuntimeAttributeWatcher::Unregister(unsigned id)
	{
		auto it = m_attributes.find(id);
		if (it == m_attributes.end())
		{
			return false;
		}

		m_attributes.erase(it);
		return true;
	}

	bool RuntimeAttributeWatcher::MatchOne(const INTERN_STRING& key, AttributeMatched updater)
	{
		for (auto& attribute : m_attributes)
		{
			if (StringMatcher::Match(attribute.second->GetName(), key))
			{
				updater(*attribute.second);
				return true;
			}
		}

		return false;
	}

	bool RuntimeAttributeWatcher::SearchAll(const INTERN_STRING& key, AttributeSearched searched)
	{
		bool has_searched = false;

		for (auto& attribute : m_attributes)
		{
			if (StringMatcher::Search(attribute.second->GetName(), key))
			{
				searched(*attribute.second);
				has_searched = true;
			}
		}

		return has_searched;
	}

}