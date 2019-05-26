#pragma once

#include <string>
#include "Command.h"

using namespace Leviathan;

namespace SOFilter
{
	struct DataUpdateCommandParameter
	{
		std::string data_folder;
		std::string data_format;
		unsigned start_index;
		unsigned end_index;
	};

	class DataUpdateCommand : public Command
	{
	public:
		DataUpdateCommand(const DataUpdateCommandParameter& parameter);

		bool Do();
		bool Undo();

	private:
		DataUpdateCommandParameter m_parameter;
	};
}