#pragma once

#include <vector>
#include "PointCloud.h"
#include "Singleton.h"
#include "ThreadRecorder.h"

using namespace Leviathan;

namespace SOFilter
{	
	/*
		FolderDataSchema provide two member for describing which file should load and load order.
		eg:
			dataFormat = "%d.ply"
			startIndex = 0
			endIndex = 999

			From this instance I should load file "0.ply" to "000.ply". 
	*/

	struct FolderDataSchema
	{
		std::string data_file_folder;
		std::string data_file_format;
		unsigned start_index;
		unsigned end_index;
	};

	class SOFDataCenter : public ThreadRecorder
	{
	public:
		DECLARE_SELF_TO_SINGLETON(SOFDataCenter)

		static SOFDataCenter& Instance();
		bool LoadPointCloud(const char* pFile);
		bool LoadPointCloudFolder(const FolderDataSchema& schema);
		unsigned PointCloudCount() const;

		LSPtr<PointCloudf> GetPointCloudByIndex(unsigned index);
		LSPtr<PointCloudf> GetOnePointCloud(unsigned& out_index) const;

	private:
		SOFDataCenter();
		std::vector<LSPtr<PointCloudf>> m_point_clouds;
	};
}