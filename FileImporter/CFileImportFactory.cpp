#include "CFileImportFactory.h"
#include "CModelStruct.h"
#include <string>
#include <mutex>

using namespace Leviathan;

LPtr<IFileImportFactory> CFileImportFactory::m_spFileImportFactory = nullptr;

Leviathan::LPtr<Leviathan::IModelFile> Leviathan::CFileImportFactory::LoadFile(const char* fileName)
{
	std::string fileNameString(fileName);
	return LoadFile(fileNameString);
}

Leviathan::LPtr<Leviathan::IFileImportFactory> Leviathan::CFileImportFactory::GetFileImportFactory()
{
	static std::once_flag sFlag;

	if (!m_spFileImportFactory)
	{
		std::call_once(sFlag, [&]()
		{
			LeviathanOutStream << "File import factory inited." << std::endl;
			m_spFileImportFactory = LPtr<IFileImportFactory>(new CFileImportFactory());
		});
	}

	return m_spFileImportFactory;
}

bool Leviathan::CFileImportFactory::RegisterImporter(std::string typeName, LPtr<IFileImporter> pImporter)
{
	auto itImporter = m_registerFileImport.find(typeName);
	if (itImporter != m_registerFileImport.end())
	{
		LeviathanOutStream << "[WARN] Try to add exist file importer." << std::endl;
		return false;
	}

	m_registerFileImport.insert(std::make_pair(typeName, pImporter));
	return true;
}

Leviathan::CFileImportFactory::CFileImportFactory()
{

}

Leviathan::LPtr<Leviathan::IModelFile> Leviathan::CFileImportFactory::LoadFile(std::string fileName)
{
	auto modelStruct = new CModelStruct();

	// Get file extension type
	auto uLastDotIndex = fileName.find_last_of('.');
	if (uLastDotIndex == std::string::npos)
	{
		LeviathanOutStream << "[ERROR] Invalid file name." << std::endl;
		return nullptr;
	}

	auto strFileExtension = fileName.substr(uLastDotIndex + 1);
	auto itImporter = m_registerFileImport.find(strFileExtension);
	if (itImporter == m_registerFileImport.end())
	{
		LeviathanOutStream << "[WARN] Unsupported file extension : " << strFileExtension <<std::endl;
		return nullptr;
	}

	return itImporter->second->LoadFile(fileName.c_str());
}
