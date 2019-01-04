#include <memory>
#include <iostream>
#include "RenderWindow.h"
#include "EventSystem.h"
using namespace Leviathan;

int main()
{
	LPtr<EventSystem> pEventSystem = new EventSystem();
	LPtr<RenderWindow> pRenderWindow = new RenderWindow(pEventSystem, Leviathan::IScene::EST_TRID);
	pEventSystem->AddEventListener(Event::EventType::INPUT_EVENT, TryCast<RenderWindow, EventListener>(pRenderWindow));

	pRenderWindow->Run();
}

