#include <gtest/gtest.h>
#include "PresenterScheduler.h"

using namespace Leviathan;

TEST(PresenterScheduler, logic_test)
{
	auto& scheduler = PresenterScheduler::Instance();
	for (unsigned i = 0; i < 20; i++)
	{
		scheduler.Update();
		Sleep(100);
	}

	scheduler.SetDone();
}