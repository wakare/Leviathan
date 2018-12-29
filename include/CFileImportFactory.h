#pragma once
#include "IFileImportFactory.h"
#include <map>

namespace Leviathan
{
	class CFileImportFactory : public IFileImportFactory
	{
	public:
		std::vector<LPtr<IModelStruct>> LoadFile(const char* fileName);
		std::vector<LPtr<IModelStruct>> LoadFile(std::string fileName);

		// Should only be called in main thread
		static LPtr<IFileImportFactory> GetFileImportFactory();

		bool RegisterImporter(std::string typeName, LPtr<IFileImporter> pImporter);
	private:
		CFileImportFactory();
		std::vector<LPtr<IModelStruct>> _loadModelByAssimp(const std::string& strFileName);

		static LPtr<IFileImportFactory> m_spFileImportFactory;
		std::map<std::string, LPtr<IFileImporter>> m_registerFileImport;
	};
}