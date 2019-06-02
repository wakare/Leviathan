/*
	LevToolInterface is a tool interface for user to convert external data struct to leviathan internal data struct and do other thing more easier.
*/

#pragma once
#include <vector>
#include "LPtr.h"
#include "PointCloud.h"

namespace Leviathan
{
	namespace Scene
	{
		class LevSceneNode;
	}

	class IMesh;

	class LevToolInterface
	{
	public:
		static bool LoadPointCloudFile(const char * file, LPtr<PointCloudf>& out);
		static bool LoadMesh(const char* file, std::vector<LPtr<IMesh>>& out);

		static bool SetPointCloudData(LPtr<PointCloudf> point_cloud, LPtr<Scene::LevSceneNode> out_node);
		static bool SetMeshData(const std::vector<LPtr<IMesh>>& point_cloud, LPtr<Scene::LevSceneNode> out_node);
	};
}