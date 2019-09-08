#pragma once

#include <vector>
#include "LSPtr.h"
#include "IFileImporter.h"

namespace Leviathan
{
	class IFileImportFactory
	{
	public:
		virtual std::vector<LSPtr<IMesh>> LoadFile(const char* fileName) = 0;
		virtual bool RegisterImporter(std::string typeName, LSPtr<IFileImporter> pImporter) = 0;

		static LSPtr<IFileImportFactory> GetFileImportFactory() { return nullptr; };

	protected:
		IFileImportFactory() {};
	};
}