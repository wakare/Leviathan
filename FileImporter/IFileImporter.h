#pragma once
#include "IModelStruct.h"
#include "LPtr.h"
#include <vector>

namespace Leviathan 
{
	class IFileImporter
	{
	public:
		IFileImporter() {};

		virtual bool RegisterToFactory() = 0;
		virtual std::string TypeName() = 0;
		virtual std::vector<LPtr<IModelStruct>> LoadFile(const char* fileName) = 0;
	};
}