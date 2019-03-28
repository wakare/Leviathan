#include <gtest/gtest.h>
#include "LevScheduler.h"
#include "LevCoroutine.h"

using namespace Leviathan;

class TestScheduler : public LevScheduler<int>
{
public:
	void Update()
	{
		Tick();
	}
};

TEST(ModelScheduler, normal_test) {

	TestScheduler scheduler;

	int container = 1;
	scheduler.AddTask([&container](CoPullType<int>& sink)
	{
		while (true)
		{
			container = 2 * container;
			sink();
		}
	});

	for (int i = 0; i < 15; i++)
	{
		scheduler.Update();
		EXPECT_EQ(container, pow(2, i + 1));
	}
}
