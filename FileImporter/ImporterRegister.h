#pragma once
#include "CSTLFileImporter.h"

namespace Leviathan
{
	bool RegisterImporter()
	{
		// Register
		auto stlImporter = Leviathan::CSTLFileImporter::GetInstance();
		
		stlImporter->RegisterToFactory();
	}
}