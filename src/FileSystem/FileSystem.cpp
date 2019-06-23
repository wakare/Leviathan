#include <iostream>
#include "LevFileSystem.h"
#include "NodeVisitor.h"

class FileNodeVisitor : public NodeVisitor<LevFileDesc>
{
public:
	virtual void Apply(Node<LevFileDesc>& node);
	virtual void Apply(const Node<LevFileDesc>& node);

private:
	void ApplyImpl(const Node<LevFileDesc>& node);
};

void FileNodeVisitor::Apply(Node<LevFileDesc>& node)
{
	ApplyImpl(node);
}

void FileNodeVisitor::Apply(const Node<LevFileDesc>& node)
{
	ApplyImpl(node);
}

void FileNodeVisitor::ApplyImpl(const Node<LevFileDesc>& node)
{
	auto& data = node.GetNodeData();
	std::cout << ((data->type == FileType::EFT_DIR_FILE) ? "Directory: " : "Regular: ") << data->file_name << std::endl;

	for (auto& child : node.GetChildren())
	{
		Apply(*child);
	}
}

int main(int argc, char** argv)
{
	if (argc <= 1)
	{
		return -1;
	}

	const char* file_directory = argv[1];

	LPtr<LevFileNode> root_node = nullptr;
	LevFileSystem::LoadDirectory(file_directory, root_node);

	FileNodeVisitor visitor;
	visitor.Apply(*root_node);

	return 0;
}