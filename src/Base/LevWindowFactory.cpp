#include "LevWindowFactory.h"
#include "ILevWindow.h"
#include "LevOpenGLWindow.h"

namespace Leviathan
{
	LevWindowFactory::LevWindowFactory()
	{
	}

	bool LevWindowFactory::Create(LevWindowType type, LPtr<ILevWindow>& out)
	{
		LPtr<ILevWindow> pWindow = nullptr;
		switch (type)
		{
		case ELWT_OPENGL:
		{
			pWindow = new LevOpenGLWindow;
			break;
		}

		default:
			return false;
		}

		out = pWindow;
		return true;
	}
}


