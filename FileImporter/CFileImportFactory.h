#pragma once
#include "IFileImportFactory.h"
#include <map>

namespace Leviathan
{
	class CFileImportFactory : public IFileImportFactory
	{
	public:
		LPtr<IModelStruct> LoadFile(const char* fileName);
		LPtr<IModelStruct> LoadFile(std::string fileName);

		// Should only be called in main thread
		static LPtr<IFileImportFactory> GetFileImportFactory();

		bool RegisterImporter(std::string typeName, LPtr<IFileImporter> pImporter);
	private:
		CFileImportFactory();

		static LPtr<IFileImportFactory> m_spFileImportFactory;
		std::map<std::string, LPtr<IFileImporter>> m_registerFileImport;
	};
}