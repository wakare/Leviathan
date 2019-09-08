#pragma once

#include <map>
#include "IFileImportFactory.h"
#include "LevCoreExport.h"

namespace Leviathan
{
	class LEV_CORE_API FileImportFactory : public IFileImportFactory
	{
	public:
		std::vector<LSPtr<IMesh>> LoadFile(const char* fileName);
		std::vector<LSPtr<IMesh>> LoadFile(std::string fileName);

		// Should only be called in main thread
		static LSPtr<IFileImportFactory> GetFileImportFactory();

		bool RegisterImporter(std::string typeName, LSPtr<IFileImporter> pImporter);
	private:
		FileImportFactory();
		std::vector<LSPtr<IMesh>> _loadModelByAssimp(const std::string& strFileName);

		static LSPtr<IFileImportFactory> m_spFileImportFactory;
		std::map<std::string, LSPtr<IFileImporter>> m_registerFileImport;
	};
}