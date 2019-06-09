#include "LevFileSystem.h"
#include <string>

namespace bf = boost::filesystem;

bool LevFileSystem::LoadDirectory(const char * path, LPtr<LevFileNode>& out)
{
	bf::path bfPath(path);
	EXIT_IF_FALSE(bf::exists(bfPath));
	EXIT_IF_FALSE(bf::is_directory(bfPath));
	EXIT_IF_FALSE(_loadDirectoryExceptFolder(bfPath, out));

	return true;
}

bool LevFileSystem::_loadDirectoryExceptFolder(bf::path& path, LPtr<LevFileNode>& out)
{
	EXIT_IF_FALSE(bf::exists(path));
	EXIT_IF_FALSE(bf::is_directory(path));

	LPtr<LevFileDesc> desc = new LevFileDesc;
	desc->file_name = path.filename().string();
	desc->type = FileType::EFT_DIR_FILE;

	out.Reset(new LevFileNode(desc));
	std::vector<bf::path> directorys;

	bf::recursive_directory_iterator itBegin(path), itEnd;
	while (itBegin != itEnd)
	{
		if (!bf::is_directory(itBegin->path()))
		{
			LPtr<LevFileDesc> desc = new LevFileDesc;
			desc->file_name = itBegin->path().filename().string();
			desc->type = FileType::EFT_REGULAR_FILE;

			LPtr<Node<LevFileDesc>> file = new LevFileNode(desc);
			out->AddChild(file);
		}

		else
		{
			directorys.push_back(itBegin->path());
		}

		itBegin++;
	}

	for (auto& p : directorys)
	{
		LPtr<LevFileNode> out;
		EXIT_IF_FALSE (_loadDirectoryExceptFolder(p, out));

		out->AddChild(TryCast<LevFileNode, Node<LevFileDesc>>(out));
	}

	return true;
}

LevFileNode::LevFileNode(LPtr<LevFileDesc> desc)
	: Node<LevFileDesc>(desc)
{

}
