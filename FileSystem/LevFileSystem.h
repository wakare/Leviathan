#pragma once

#include "Node.h"
#include "GlobalDef.h"
#include <boost/filesystem.hpp>

using namespace Leviathan;

enum FileType
{
	EFT_REGULAR_FILE,
	EFT_DIR_FILE
};

struct LevFileDesc
{
	FileType type;
	std::string file_name;
};

class LevFileNode : public Node<LevFileDesc>
{
public:
	UNIQUE_INSTANCE(LevFileNode)

	LevFileNode(LPtr<LevFileDesc> desc);
};

class LevFileSystem
{
public:
	static bool LoadDirectory(const char* path, LPtr<LevFileNode>& out);

private:
	static bool _loadDirectoryExceptFolder(boost::filesystem::path& path, LPtr<LevFileNode>& out);
};
