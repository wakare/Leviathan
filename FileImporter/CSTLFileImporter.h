#pragma once
#include "IFileImporter.h"
#include "CModelStruct.h"
#include "IModelStruct.h"

namespace Leviathan
{
	class CSTLFileImporter : public IFileImporter
	{
	public:
		static LPtr<IFileImporter> GetInstance();
		std::string TypeName();
		LPtr<IModelFile> LoadFile(const char* fileName);
		bool RegisterToFactory();

	private:
		CSTLFileImporter();
		static LPtr<IFileImporter> m_spSTLFileImporter;
	};
}