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

	LevFileNode(LPtr<LevFileDesc> desc);
};

class LevFileSystem
{
public:
	static bool LoadDirectory(const char* path, LPtr<LevFileNode>& out);

private:
	static bool _recursiveLoadDirectory(boost::filesystem::path& path, LPtr<LevFileNode>& out);
};
