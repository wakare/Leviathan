#pragma once
#include "LPtr.h"
#include "IFileImporter.h"

namespace Leviathan
{
	class IFileImportFactory
	{
	public:
		virtual LPtr<IModelFile> LoadFile(const char* fileName) = 0;
		virtual bool RegisterImporter(std::string typeName, LPtr<IFileImporter> pImporter) = 0;

		static LPtr<IFileImportFactory> GetFileImportFactory() {};

	protected:
		IFileImportFactory() {};
	};
}