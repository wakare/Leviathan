#pragma once
#include "IModelStruct.h"
#include "LPtr.h"

namespace Leviathan 
{
	class IFileImporter
	{
	public:
		IFileImporter() {};

		virtual bool RegisterToFactory() = 0;
		virtual std::string TypeName() = 0;
		virtual LPtr<IModelFile> LoadFile(const char* fileName) = 0;
	};
}