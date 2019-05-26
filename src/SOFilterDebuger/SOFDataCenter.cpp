#include "SOFDataCenter.h"
#include "LevToolInterface.h"

namespace SOFilter
{
	SOFDataCenter::SOFDataCenter()
	{

	}

	SOFDataCenter & SOFDataCenter::Instance()
	{
		return Singleton<SOFDataCenter>::Instance();
	}

	bool SOFDataCenter::LoadPointCloud(const char * pFile)
	{
		LPtr<PointCloudf> point_cloud;
		EXIT_IF_FALSE(LevToolInterface::LoadPointCloudFile(pFile, point_cloud));

		m_point_clouds.push_back(point_cloud);
		return true;
	}

	bool SOFDataCenter::LoadPointCloudFolder(const FolderDataSchema& schema)
	{
		for (unsigned i = schema.start_index; i <= schema.end_index; i++)
		{
			// TODO: configuratable max path length
			char path[500];
			auto fullPath = schema.data_file_folder + "/" + schema.data_file_format;
			snprintf(path, sizeof(path), fullPath.c_str(), i);

			EXIT_IF_FALSE(LoadPointCloud(path));
		}

		return true;
	}

	unsigned SOFDataCenter::PointCloudCount() const
	{
		return m_point_clouds.size();
	}

	Leviathan::LPtr<PointCloudf> SOFDataCenter::GetPointCloudByIndex(unsigned index)
	{
		EXIT_IF_FALSE(m_point_clouds.size() > index);

		return m_point_clouds[index];
	}

	Leviathan::LPtr<PointCloudf> SOFDataCenter::GetOnePointCloud(unsigned& out_index) const
	{
		static unsigned _current_index = 0;
		EXIT_IF_FALSE(m_point_clouds.size() > _current_index);

		out_index = _current_index;
		return m_point_clouds[_current_index++];
	}

}