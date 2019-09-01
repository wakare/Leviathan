#pragma once

namespace Leviathan
{
	class Event;
	class EventListener
	{
	public:
		virtual ~EventListener() = default;
		virtual void Accept(Event& event) = 0;
	};
}