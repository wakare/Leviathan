#pragma once

namespace Leviathan
{
	class Event;
	class EventListener
	{
	public:
		virtual void Accept(Event& event) = 0;
	};
}