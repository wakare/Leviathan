#include "LevFileSystem.h"
#include <string>

namespace bf = boost::filesystem;

bool LevFileSystem::LoadDirectory(const char * path, LPtr<LevFileNode>& out)
{
	bf::path bfPath(path);
	EXIT_IF_FALSE(bf::exists(bfPath));
	EXIT_IF_FALSE(bf::is_directory(bfPath));
	EXIT_IF_FALSE(_recursiveLoadDirectory(bfPath, out));

	return true;
}

bool LevFileSystem::_recursiveLoadDirectory(bf::path& path, LPtr<LevFileNode>& out)
{
	EXIT_IF_FALSE(bf::exists(path));
	EXIT_IF_FALSE(bf::is_directory(path));

	LPtr<LevFileDesc> desc = new LevFileDesc;
	desc->file_name = path.filename().string();
	desc->type = LevFileType::EFT_DIR_FILE;

	out.Reset(new LevFileNode(desc));
	std::vector<bf::path> directorys;

	for (auto& entry : bf::directory_iterator(path))
	{
		bool isDirectory = bf::is_directory(entry.path());

		if (!isDirectory)
		{
			LPtr<LevFileDesc> desc = new LevFileDesc;
			desc->file_name = entry.path().filename().string();
			desc->type = LevFileType::EFT_REGULAR_FILE;

			LPtr<Node<LevFileDesc>> file = new LevFileNode(desc);
			out->AddChild(file);
		}

		else
		{
			directorys.push_back(entry.path());
		}
	}

	for (auto& p : directorys)
	{
		LPtr<LevFileNode> directory_out;
		EXIT_IF_FALSE (_recursiveLoadDirectory(p, directory_out));

		out->AddChild(TryCast<LevFileNode, Node<LevFileDesc>>(directory_out));
	}

	return true;
}

LevFileNode::LevFileNode(LPtr<LevFileDesc> desc)
	: Node<LevFileDesc>(desc)
{

}
