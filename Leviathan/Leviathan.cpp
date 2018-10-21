#include <memory>
#include <iostream>
//#include "Node.h"
//#include "NodeVisitor.h"
#include "RenderWindow.h"

#if (false)
template<class T>
class MyNodeVisitor : public NodeVisitor<T>
{
public:
	MyNodeVisitor(TRAVERSE_MODE mode) :NodeVisitor(mode) {}

	virtual void apply(Node<T>& node);
};

template<class T>
void MyNodeVisitor<T>::apply(Node<T>& node)
{
	if (GetTraverseMode() == NodeVisitor<T>::TRAVERSE_MODE::NONE)
	{
		return;
	}

	std::cout << *(node.GetNodeData()) << std::endl;
	if (GetTraverseMode() == NodeVisitor<T>::TRAVERSE_MODE::ONLY)
	{
		return;
	}

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

	rootNode->accept(MyNodeVisitor<int>(MyNodeVisitor<int>::TRAVERSE_MODE::ALL));

	return 0;
}
#endif

int main()
{
	std::shared_ptr<EventSystem> pEventSystem = std::make_shared<EventSystem>();
	std::shared_ptr<RenderWindow> pRenderWindow = std::make_shared<RenderWindow>(pEventSystem);
	pEventSystem->AddEventListener(Event::EventType::INPUT_EVENT, pRenderWindow);

	pRenderWindow->Run();
}

