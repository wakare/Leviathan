#pragma once

#include "IFileImporter.h"
#include "MeshImpl.h"
#include "IMesh.h"
#include "Singleton.h"

namespace Leviathan
{
	class STLFileImporter : public IFileImporter
	{
		DECLARE_SELF_TO_SINGLETON(STLFileImporter)
	public:
		static IFileImporter& GetInstance();
		std::string TypeName();
		std::vector<LSPtr<IMesh>> LoadFile(const char* fileName);
		bool RegisterToFactory();

	private:
		STLFileImporter();
	};
}