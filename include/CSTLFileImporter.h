#pragma once

#include "IFileImporter.h"
#include "CMesh.h"
#include "IMesh.h"

namespace Leviathan
{
	class CSTLFileImporter : public IFileImporter
	{
	public:
		static LPtr<IFileImporter> GetInstance();
		std::string TypeName();
		std::vector<LPtr<IMesh>> LoadFile(const char* fileName);
		bool RegisterToFactory();

	private:
		CSTLFileImporter();
		static LPtr<IFileImporter> m_spSTLFileImporter;
	};
}