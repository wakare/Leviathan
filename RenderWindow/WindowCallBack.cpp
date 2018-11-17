#include "WindowCallBack.h"
#include "LPtr.h"

namespace Leviathan
{
	LPtr<EventSystem> WindowCallBack::m_spEventSystem = nullptr;
	GLFWInputMapEventCode WindowCallBack::m_sInputMap;
	GLFWActionMapEvent WindowCallBack::m_sActionMap;
}