#include "VFXSampleBaseViewer.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

int main()
{
	Leviathan::Viewer::VFXSampleBaseViewer viewer;
	viewer.Run();

	_CrtDumpMemoryLeaks();

	return 0;
}