#pragma once

#include "CSTLFileImporter.h"

namespace Leviathan
{
	bool RegisterImporter()
	{
		// Register
		auto& stlImporter = Leviathan::CSTLFileImporter::GetInstance();
		
		if (!stlImporter.RegisterToFactory())
		{
			LeviathanOutStream << "[ERROR] Register to factory failed." << std::endl;
			return false;
		}

		return true;
	}
}