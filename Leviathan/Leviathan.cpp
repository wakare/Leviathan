#include <memory>
#include <iostream>
#include "Node.h"
#include "NodeVisitor.h"

template<class T>
class MyNodeVisitor : public NodeVisitor<T>
{
public:
	virtual void apply(Node<T>& node);
};

template<class T>
void MyNodeVisitor<T>::apply(Node<T>& node)
{
	std::cout << *(node.GetNodeData()) << std::endl;
	for (auto& pChild : node.GetChildren())
	{
		pChild->accept(*this);
	}
}

int main()
{
	std::shared_ptr<Node<int>> rootNode = std::make_shared<Node<int>>(std::shared_ptr<int>(new int(0)));

	rootNode->AddChild(std::make_shared<Node<int>>(std::shared_ptr<int>(new int(1))));
	rootNode->AddChild(std::make_shared<Node<int>>(std::shared_ptr<int>(new int(2))));
	rootNode->AddChild(std::make_shared<Node<int>>(std::shared_ptr<int>(new int(3))));
	rootNode->AddChild(std::make_shared<Node<int>>(std::shared_ptr<int>(new int(4))));

	rootNode->accept(MyNodeVisitor<int>());

	return 0;
}

