#pragma once

#include "STLFileImporter.h"

namespace Leviathan
{
	bool RegisterImporter()
	{
		// Register
		auto& stlImporter = Leviathan::STLFileImporter::GetInstance();
		
		if (!stlImporter.RegisterToFactory())
		{
			LeviathanOutStream << "[ERROR] Register to factory failed." << std::endl;
			return false;
		}

		return true;
	}
}