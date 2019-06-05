#pragma once

#include <gl/glew.h>
#include <glfw/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

namespace Leviathan
{
	class LevGLFWWindowWrapper : public GLFWwindow
	{

	};
}