#pragma once

#include "IFileImporter.h"
#include "MeshImpl.h"
#include "IMesh.h"
#include "Singleton.h"

namespace Leviathan
{
	class CSTLFileImporter : public IFileImporter
	{
		DECLARE_SELF_TO_SINGLETON(CSTLFileImporter)
	public:
		static IFileImporter& GetInstance();
		std::string TypeName();
		std::vector<LPtr<IMesh>> LoadFile(const char* fileName);
		bool RegisterToFactory();

	private:
		CSTLFileImporter();
	};
}