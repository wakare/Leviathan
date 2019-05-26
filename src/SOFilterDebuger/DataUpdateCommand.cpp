#include "DataUpdateCommand.h"
#include "SOFDataCenter.h"

namespace SOFilter
{
	DataUpdateCommand::DataUpdateCommand(const DataUpdateCommandParameter & parameter)
		: m_parameter(parameter)
	{
	}

	bool DataUpdateCommand::Do()
	{
		FolderDataSchema schema;
		schema.data_file_folder = m_parameter.data_folder;
		schema.data_file_format = m_parameter.data_format;
		schema.start_index = m_parameter.start_index;
		schema.end_index = m_parameter.end_index;

		return SOFDataCenter::Instance().LoadPointCloudFolder(schema);
	}

	bool DataUpdateCommand::Undo()
	{
		// We can not undo data update command, so just return false.
		return false;
	}
}