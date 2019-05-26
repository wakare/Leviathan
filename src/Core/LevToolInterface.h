/*
	LevToolInterface is a tool interface for user to convert external data struct to leviathan internal data struct and do other thing more easier.
*/

#pragma once
#include "LPtr.h"
#include "PointCloud.h"

namespace Leviathan
{
	namespace Scene
	{
		class LevSceneNode;
	}

	class LevToolInterface
	{
	public:
		static bool LoadPointCloudFile(const char * file, LPtr<PointCloudf>& out);
	};
}