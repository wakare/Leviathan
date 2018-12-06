#include "KOcTree.h"

namespace Leviathan
{
	KSPtr<KOcTree> CreateParentOcTreeBasedChild(const KSPtr<AABBf>& pAABB, const KSPtr<KOcTree>& pChild)
	{
		if (pChild->GetAABB().Inside(*pAABB))
		{
			//KLog::Log("[INFO] No need create new OcTree.");
			return pChild;
		}

		AABBf MergeAABB = pAABB->Merge(pChild->GetAABB());

		KSPtr<KOcTree> result = KSPtr<KOcTree>(new KOcTree(nullptr, MergeAABB, nullptr));
		if (!result)
		{
			KLog::Log("[ERROR] Create OcTree failed.");
			return pChild;
		}

		auto& baseAABB = pChild->GetAABB();
		std::vector<KSPtr<AABBf>> pAABBfVec;

		for (int i = -1; i <= 1; i++)
		{
			for (int j = -1; j <= 1; j++)
			{
				for (int k = -1; k <= 1; k++)
				{
					if (i == 0 && j == 0 && k == 0)
					{
						continue;
					}

					// Calculate aabb
					float _min[3];
					float _max[3];

					_min[0] = (i == -1) ? MergeAABB.m_min.coord[0] : ((i == 0) ? baseAABB.m_min.coord[0] : baseAABB.m_max.coord[0]);
					_min[1] = (j == -1) ? MergeAABB.m_min.coord[1] : ((j == 0) ? baseAABB.m_min.coord[1] : baseAABB.m_max.coord[1]);
					_min[2] = (k == -1) ? MergeAABB.m_min.coord[2] : ((k == 0) ? baseAABB.m_min.coord[2] : baseAABB.m_max.coord[2]);

					_max[0] = (i == -1) ? baseAABB.m_min.coord[0] : ((i == 0) ? baseAABB.m_max.coord[0] : MergeAABB.m_max.coord[0]);
					_max[1] = (j == -1) ? baseAABB.m_min.coord[1] : ((j == 0) ? baseAABB.m_max.coord[1] : MergeAABB.m_max.coord[1]);
					_max[2] = (k == -1) ? baseAABB.m_min.coord[2] : ((k == 0) ? baseAABB.m_max.coord[2] : MergeAABB.m_max.coord[2]);

					KSPtr<AABBf> _pAABB = KSPtr<AABBf>(new AABBf(_min, _max));
					pAABBfVec.push_back(_pAABB);
				}
			}
		}

		if (!result->_initChildrenByAABBVec(pAABBfVec))
		{
			KLog::Log("[ERROR] Init children AABB failed.");
			return nullptr;
		}

		// Add one child
		pChild->SetParent(result);
		result->_addChildOcTree(pChild);

		return result;
	};

	// Only interface for user to add node, please use return value as root OcTree
	KSPtr<KOcTree> AddNodeAndUpdateOcTree(KSPtr<KOcTree> pOcTree, const std::vector<KSPtr<IOcTreeNode>>& needAddNodeVec)
	{
		{
			bool bInitMinAndMax = false;
			float min[3];
			float max[3];

			for (auto& pNode : needAddNodeVec)
			{
				auto& nodeCoord = pNode->GetCoord();

				if (!bInitMinAndMax)
				{
					min[0] = nodeCoord.coord[0];
					min[1] = nodeCoord.coord[1];
					min[2] = nodeCoord.coord[2];

					max[0] = nodeCoord.coord[0];
					max[1] = nodeCoord.coord[1];
					max[2] = nodeCoord.coord[2];

					bInitMinAndMax = true;
					continue;
				}

				if (nodeCoord.coord[0] < min[0])
				{
					min[0] = nodeCoord.coord[0];
				}
				if (nodeCoord.coord[1] < min[1])
				{
					min[1] = nodeCoord.coord[1];
				}
				if (nodeCoord.coord[2] < min[2])
				{
					min[2] = nodeCoord.coord[2];
				}

				if (nodeCoord.coord[0] > max[0])
				{
					max[0] = nodeCoord.coord[0];
				}
				if (nodeCoord.coord[1] > max[1])
				{
					max[1] = nodeCoord.coord[1];
				}
				if (nodeCoord.coord[2] > max[2])
				{
					max[2] = nodeCoord.coord[2];
				}
			}

			KSPtr<AABBf> pAABB;
			pAABB.reset(new AABBf(min, max));
			auto pResult = CreateParentOcTreeBasedChild(pAABB, pOcTree);

			if (!pResult->_addNode(needAddNodeVec))
			{
				KLog::Log("[ERROR] Add node failed.");
				throw "Exception";
			}

			return pResult;
		}
	}
}