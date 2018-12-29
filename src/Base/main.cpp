#include "KOcTree.h"
#include "KProfile.h"
#include <string>

using namespace OcTree;

int main()
{
	// Root node
	KSPtr<KOcTree> pOcTree;

	unsigned uTestNodeCount = 3000 /*3000000*/;
	KSPtr<AABBf> pAABB = KSPtr<AABBf>(new AABBf());
	bool bInitAABB = false;

	srand(GetTickCount64());

	unsigned long long uTotalCostTime = 0U;

	// Debug 
	Point3Df debugPoint = { 10.0f, 10.0f, 10.0f };
	float fDebugRadius = 2000.0f;
		for (unsigned j = 0; j < 2000; j++)
		{
			std::vector<KSPtr<IOcTreeNode>> needAddNodeVec;
			float _min[3];
			float _max[3];
			bool bInited = false;
			float fScaleRatio = min(j + 1, 100);

			for (unsigned i = 0; i < uTestNodeCount; i++)
			{
				KSPtr<IOcTreeNode> pNode;
				auto nRandomValue0 = rand() - (RAND_MAX / 2);
				auto nRandomValue1 = rand() - (RAND_MAX / 2);
				auto nRandomValue2 = rand() - (RAND_MAX / 2);

				float coord[3] = { nRandomValue0 * fScaleRatio, nRandomValue1 * fScaleRatio, nRandomValue2 * fScaleRatio };

				if (!bInited)
				{
					_min[0] = coord[0];
					_min[1] = coord[1];
					_min[2] = coord[2];

					_max[0] = coord[0];
					_max[1] = coord[1];
					_max[2] = coord[2];
					
					bInited = true;
				}
				
				if (coord[0] < _min[0])
				{
					_min[0] = coord[0];
				}
				if (coord[1] < _min[1])
				{
					_min[1] = coord[1];
				}
				if (coord[2] < _min[2])
				{
					_min[2] = coord[2];
				}

				if (coord[0] > _max[0])
				{
					_max[0] = coord[0];
				}
				if (coord[1] > _max[1])
				{
					_max[1] = coord[1];
				}
				if (coord[2] > _max[2])
				{
					_max[2] = coord[2];
				}

// 				if (Point3Df::Distance(coord, debugPoint) < fDebugRadius)
// 				{
// 					static unsigned uLoopCount = 0;
// 					char buffer[100];
// 					snprintf(buffer, sizeof(buffer), "[INFO] Valid coord : %f, %f, %f. %u", coord[0], coord[1], coord[2], ++uLoopCount);
// 					KLog::Log(buffer);
// 				}

				pNode.reset(new IOcTreeNode(coord));
				needAddNodeVec.push_back(pNode);
			}

			//ProfileTimerTick
			auto tempBegin = GetTickCount64();
			if (!bInitAABB)
			{
				pAABB->min = { _min[0], _min[1], _min[2] };
				pAABB->max = { _max[0], _max[1], _max[2] };

// 				float minLimit = static_cast<float>(INT_MIN);
// 				float maxLimit = static_cast<float>(INT_MAX);
// 				pAABB->min = { minLimit, minLimit, minLimit };
// 				pAABB->max = { maxLimit, maxLimit, maxLimit };

				pOcTree.reset(new KOcTree(nullptr, *pAABB));

				bInitAABB = true;
			}

			pOcTree = AddNode(pOcTree, needAddNodeVec);

			uTotalCostTime += (GetTickCount64() - tempBegin);
		}

	KLog::Log("[INFO] Total cost time: " + std::to_string(uTotalCostTime));
// 	ProfileTimerTick
// 	KSPtr<KOcTree> newOcTree;
// 	pOcTree->ReConstructAverageOcTree(newOcTree);
// 	ProfileTimerTick

// 	auto result = newOcTree->SearchRadiusNodeSet(KSPtr<IOcTreeNode>(new IOcTreeNode(debugPoint)), fDebugRadius);
// 	KLog::Log(std::to_string(result.size()));
// 
// 	for (auto& pNode : result)
// 	{
// 		KLog::Log("Coord:" + pNode->ToString());
// 	}

	KLog::Log(std::to_string(pOcTree->GetAddedNodeCount()));
	return EXIT_SUCCESS;
}
