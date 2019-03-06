#include <memory>
#include <iostream>
#include "RenderService.h"
#include "EventListener.h"
#include "Event.h"

using namespace Leviathan;

class MyEventListener : public EventListener
{
public:
	void Accept(Event& event);
};

inline void MyEventListener::Accept(Event & event)
{
	if (event.m_action == Event::KEYDOWN && event.m_code == Event::KEY_Z)
	{
		LogLine("Z keydown for main");
	}
}

bool _registerEventCallback()
{
	LPtr<EventListener> eventListener = new MyEventListener();
	EXIT_IF_FALSE(RenderService::Instance()->AddEventListener(INPUT_EVENT, eventListener));
	return true;
}

int main()
{
	RenderService::SetSceneType(IScene::EST_TRID);
	EXIT_IF_FALSE(_registerEventCallback());
	EXIT_IF_FALSE(RenderService::Instance()->Init());
	RenderService::Instance()->Run();
}

