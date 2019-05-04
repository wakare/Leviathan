#include "LevTimerTickVisitor.h"
#include "Node.h"
#include "LevSceneObject.h"
#include "LevTimer.h"
#include <windows.h>

namespace Leviathan
{
	namespace Scene
	{
		void LevTimerTickVisitor::Apply(Node<LevSceneObject>& node)
		{
			auto& nodeData = node.GetNodeData();
			auto pTimer = nodeData->GetTimer();
			if(pTimer)
			{
				auto lastTick = pTimer->GetLastTime();
				auto timeInterval = pTimer->GetTimeInterval();
				if (GetTickCount64() - lastTick > timeInterval)
				{
					pTimer->OnTimeOut();
					pTimer->UpdateCurrentTickTime();
				}
			}

			for (auto& child : node.GetChildren())
			{
				child->Accept(*this);
			}
		}

		void LevTimerTickVisitor::Apply(const Node<LevSceneObject>& node)
		{

		}

	}
}