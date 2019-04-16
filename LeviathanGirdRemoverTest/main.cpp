#include "UserInterface.h"

using namespace Leviathan;

int main(int argc, char** argv)
{
	UserInterface::Init(1080, 720, 0);

	if (argc < 2 || !argv[1])
	{
		return -1;
	}

	int nCount = 100;
	int nCurrent = 0;

	std::string path = argv[1];
	path += "\\frame_%04d.ply";
	char buf[300];

	while (true)
	{
		if(nCount > nCurrent)
		{
			memset(buf, 0, 300);
			snprintf(buf, 300, path.c_str(), nCurrent++);
			UserInterface::LoadPointCloudFile(buf);
		}
		
		UserInterface::UpdatePresenter();
	}
}