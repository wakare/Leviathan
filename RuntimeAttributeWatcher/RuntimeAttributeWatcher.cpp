#include "RuntimeAttributeWatcher.h"

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

}