#pragma once

#include <vector>
#include "IMesh.h"
#include "LPtr.h"

namespace Leviathan 
{
	class IFileImporter
	{
	public:
		IFileImporter() {};

		virtual bool RegisterToFactory() = 0;
		virtual std::string TypeName() = 0;
		virtual std::vector<LPtr<IMesh>> LoadFile(const char* fileName) = 0;
	};
}