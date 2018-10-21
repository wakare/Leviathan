#include "WindowCallBack.h"

std::shared_ptr<EventSystem> WindowCallBack::m_spEventSystem = nullptr;
GLFWInputMapEventCode WindowCallBack::m_sInputMap;
GLFWActionMapEvent WindowCallBack::m_sActionMap;