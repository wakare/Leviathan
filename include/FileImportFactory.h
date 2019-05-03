#pragma once

#include <map>
#include "IFileImportFactory.h"

namespace Leviathan
{
	class FileImportFactory : public IFileImportFactory
	{
	public:
		std::vector<LPtr<IMesh>> LoadFile(const char* fileName);
		std::vector<LPtr<IMesh>> LoadFile(std::string fileName);

		// Should only be called in main thread
		static LPtr<IFileImportFactory> GetFileImportFactory();

		bool RegisterImporter(std::string typeName, LPtr<IFileImporter> pImporter);
	private:
		FileImportFactory();
		std::vector<LPtr<IMesh>> _loadModelByAssimp(const std::string& strFileName);

		static LPtr<IFileImportFactory> m_spFileImportFactory;
		std::map<std::string, LPtr<IFileImporter>> m_registerFileImport;
	};
}