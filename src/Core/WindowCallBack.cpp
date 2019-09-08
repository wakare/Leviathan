#include "WindowCallBack.h"
#include "LSPtr.h"

namespace Leviathan
{
	GLFWInputMapEventCode WindowCallBack::m_sInputMap;
	GLFWActionMapEvent WindowCallBack::m_sActionMap;
	std::map<GLFWwindow*, EventSystem*> WindowCallBack::m_window_event_system_map;
}