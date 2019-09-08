#pragma once

#include "Node.h"
#include "GlobalDef.h"
#include <boost/filesystem.hpp>

using namespace Leviathan;

struct LevFileDesc
{
	LevFileType type;
	std::string file_name;
};

class LevFileNode : public Node<LevFileDesc>
{
public:
	UNIQUE_INSTANCE(LevFileNode)

	LevFileNode(LSPtr<LevFileDesc> desc);
};

class LevFileSystem
{
public:
	static bool LoadDirectory(const char* path, LSPtr<LevFileNode>& out);

private:
	static bool _recursiveLoadDirectory(boost::filesystem::path& path, LSPtr<LevFileNode>& out);
};
