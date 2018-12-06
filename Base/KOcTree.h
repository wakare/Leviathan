#pragma once
#include <memory>
#include <vector>
#include "KLog.h" 
#include "LPtr.h"
#include <functional>

namespace Leviathan
{
#define KSPtr LPtr
	//#define KUPtr std::unique_ptr;
#define DefaultOcTreeSubTreeCount 8

	struct Point3Df
	{
		Point3Df()
		{
			memset(coord, 0, sizeof(float) * 3);
		};

		Point3Df(float x, float y, float z)
		{
			coord[0] = x;
			coord[1] = y;
			coord[2] = z;
		};

		Point3Df(float* pdata)
		{
			memcpy(coord, pdata, sizeof(float) * 3);
		};

		static float Distance(const Point3Df& lhs, const Point3Df& rhs)
		{
			return sqrtf((lhs.coord[0] - rhs.coord[0]) * (lhs.coord[0] - rhs.coord[0]) +
						 (lhs.coord[1] - rhs.coord[1]) * (lhs.coord[1] - rhs.coord[1]) +
						 (lhs.coord[2] - rhs.coord[2]) * (lhs.coord[2] - rhs.coord[2]));
		}

		bool operator<(const Point3Df& rhs) const
		{
			if (coord[0] < rhs.coord[0])
			{
				return true;
			}

			else if (coord[0] > rhs.coord[0])
			{
				return false;
			}

			if (coord[1] < rhs.coord[1])
			{
				return true;
			}

			else if (coord[1] > rhs.coord[1])
			{
				return false;
			}

			if (coord[2] < rhs.coord[2])
			{
				return true;
			}

			else if (coord[2] > rhs.coord[2])
			{
				return false;
			}

			return false;
		};

		bool operator==(const Point3Df& rhs) const
		{
			return (coord[0] == rhs.coord[0]) && (coord[1] == rhs.coord[1]) && (coord[2] == rhs.coord[2]);
		};

		bool operator<=(const Point3Df& rhs) const 
		{
			return *(this) < rhs || *(this) == rhs;
		};

		float coord[3];
	};

	struct AABBf
	{
		Point3Df max;
		Point3Df min;

		const Point3Df& GetCenter() const
		{
			float center[3] =
			{
				(min.coord[0] + max.coord[0]) * 0.5f,
				(min.coord[1] + max.coord[1]) * 0.5f,
				(min.coord[2] + max.coord[2]) * 0.5f
			};

			return center;
		}

		float GetRadius() const
		{
			auto center = GetCenter();
			return Point3Df::Distance(center, min);
		}

		bool Inside(const Point3Df& rhs) const
		{
			return	(rhs.coord[0] <= max.coord[0] && rhs.coord[0] >= min.coord[0]) &&
					(rhs.coord[1] <= max.coord[1] && rhs.coord[1] >= min.coord[1]) && 
					(rhs.coord[2] <= max.coord[2] && rhs.coord[2] >= min.coord[2]);
		}

		bool Inside(const AABBf& rhs) const 
		{
			/*return (min <= rhs.min && rhs.max <= max);*/
			bool bMin =
				min.coord[0] < rhs.min.coord[0] &&
				min.coord[1] < rhs.min.coord[1] &&
				min.coord[2] < rhs.min.coord[2];
			if (!bMin)
			{
				return false;
			}

			bool bMax =
				max.coord[0] > rhs.max.coord[0] &&
				max.coord[1] > rhs.max.coord[1] &&
				max.coord[2] > rhs.max.coord[2];

			return bMax;
		}

		AABBf Merge(const AABBf& rhs) const 
		{
			float _min[3];
			float _max[3];

			_min[0] = fmin(min.coord[0], rhs.min.coord[0]);
			_min[1] = fmin(min.coord[1], rhs.min.coord[1]);
			_min[2] = fmin(min.coord[2], rhs.min.coord[2]);

			_max[0] = fmax(max.coord[0], rhs.max.coord[0]);
			_max[1] = fmax(max.coord[1], rhs.max.coord[1]);
			_max[2] = fmax(max.coord[2], rhs.max.coord[2]);

			return AABBf(_min, _max);
		}

		AABBf()
		{
		}

		AABBf(const Point3Df& _min, const Point3Df& _max):
			min(_min), 
			max(_max)
		{
		}
	};

	class IOcTreeNode
	{
	public:
		IOcTreeNode(const Point3Df& rhs) :
			m_coord(rhs)
		{

		}

		bool operator< (const IOcTreeNode& rhs) const
		{
			return m_coord < rhs.m_coord;
		}

		bool operator<= (const IOcTreeNode& rhs) const
		{
			return m_coord <= rhs.m_coord;
		}

		const Point3Df& GetCoord() const
		{
			return m_coord;
		}

		std::string ToString() const
		{
			char buff[100];
			snprintf(buff, sizeof(buff), " %f %f %f", m_coord.coord[0], m_coord.coord[1], m_coord.coord[2]);
			return buff;
		}

		virtual ~IOcTreeNode()
		{

		}
	private:
		Point3Df m_coord;
	};

	class KOcTree
	{
	public:
		enum ETreeType
		{
			ETT_DEFAULT,
			ETT_CUSTOM,
			ETT_UNKNOWN,
		};

		KOcTree(KOcTree* pParent, const AABBf& AABB, KSPtr<IOcTreeNode> pNodeData = nullptr) :
			m_pParent(pParent),
			m_pNodeData(pNodeData),
			m_AABB(AABB),
			m_uNodeCount(0),
			m_eType(ETT_UNKNOWN)
		{
			if (m_pNodeData)
			{
				if (!_addNode(m_pNodeData))
				{
					KLog::Log("[ERROR] Add node failed.");
					throw "Exception";
				}
			}
		}

		bool IsLeaf() const
		{
			return m_pNodeData != nullptr;
		}

		const KSPtr<IOcTreeNode>& GetLeafNode() const
		{
			return m_pNodeData;
		}

		bool IsRoot() const 
		{
			return m_pParent == nullptr;
		}

		unsigned GetAddedNodeCount() const 
		{
			return m_uNodeCount;
		}

		const AABBf& GetAABB() const
		{
			return m_AABB;
		}

		bool SetParent(KSPtr<KOcTree> pParent)
		{
			if (!pParent)
			{
				return false;
			}

			if (!pParent->m_AABB.Inside(m_AABB))
			{
				return false;
			}

			m_pParent = pParent.get();
			return true;
		}

		void Traverse(std::function<void(KOcTree& rhs)> traverseFunc, bool bRecursion)
		{
			for (auto& child : m_pChildren)
			{
				traverseFunc(*child);
				if (bRecursion)
				{
					child->Traverse(traverseFunc, bRecursion);
				}
			}
		}

		bool ReConstructAverageOcTree(KSPtr<KOcTree>& outResult)
		{
			if (outResult.get() == this)
			{
				KLog::Log("[ERROR] Invalid out result.");
				return false;
			}

			outResult.reset(new KOcTree(m_pParent, m_AABB, nullptr));
			auto traverseFunc = [&outResult](const KOcTree& rhs) { if (rhs.IsLeaf())  outResult->_addNode(rhs.GetLeafNode()); };
			// Traverse all leaf node
			Traverse(traverseFunc, true);

			return true;
		}

		friend KSPtr<KOcTree> CreateParentOcTreeBasedChild(const KSPtr<AABBf>& pAABB, const KSPtr<KOcTree>& pChild);

		friend KSPtr<KOcTree> AddNodeAndUpdateOcTree(KSPtr<KOcTree> pOcTree, const std::vector<KSPtr<IOcTreeNode>>& needAddNodeVec);

		std::vector<KSPtr<IOcTreeNode>> SearchRadiusNodeSet(KSPtr<IOcTreeNode> pNode, float fSearchRadius)
		{
			std::vector<KSPtr<IOcTreeNode>> result;
			auto coord = pNode->GetCoord();

			auto traverseFunc = [&result, &coord, fSearchRadius](const KOcTree& rhs)
			{ 
				auto _center = rhs.GetAABB().GetCenter();
				auto _radius = rhs.GetAABB().GetRadius();
				if (Point3Df::Distance(_center, coord) > fSearchRadius + _radius)
				{
					// Too far
					return;
				}

				if (rhs.IsLeaf())
				{
					auto& pLeafNode = rhs.GetLeafNode();
					auto leafCoord = pLeafNode->GetCoord();
					auto fDistance = Point3Df::Distance(coord, leafCoord);
					
					if (fDistance < fSearchRadius)
					{
						result.push_back(pLeafNode);
					}
				}
			};

			Traverse(traverseFunc, true);

			return result;
		}

		std::vector<KSPtr<IOcTreeNode>> SearchNearestNodeSet(KSPtr<IOcTreeNode> pNode, unsigned uMaxSearchCount);

	private:
		bool _addNode(const KSPtr<IOcTreeNode>& pNode)
		{
			if (!m_AABB.Inside(pNode->GetCoord()))
			{
				KLog::Log("[ERROR] Invalid node.");
				return false;
			}

			m_uNodeCount++;

			if (m_uNodeCount == 1)
			{
				m_pNodeData = pNode;
				return true;
			}

			if (m_uNodeCount == 2)
			{
				if (m_eType == ETT_UNKNOWN && !_initSubTree())
				{
					KLog::Log("[ERROR] Init subTree failed.");
					return false;
				}

				auto _index = _getSubTreeIndex(m_pNodeData);
				if (!_addNodeToSubTree(m_pNodeData, _index))
				{
					return false;
				}

				m_pNodeData = nullptr;
			}

			auto index = _getSubTreeIndex(pNode);
			if (!_addNodeToSubTree(pNode, index))
			{
				return false;
			}

			return true;
		}

		bool _addNode(const std::vector<KSPtr<IOcTreeNode>>& pNodeVec)
		{
			for (auto& pNode : pNodeVec)
			{
				if (!_addNode(pNode))
				{
					return false;
				}
			}

			return true;
		}

		// Do not use this method unless you know what you're doing
		bool _addChildOcTree(const KSPtr<KOcTree>& pOcTree)
		{
			m_pChildren.push_back(pOcTree);
			m_uNodeCount += pOcTree->m_uNodeCount;
			return true;
		}

		bool _initChildrenByAABBVec(std::vector<KSPtr<AABBf>>& pAABBVec)
		{
			if (m_eType != ETT_UNKNOWN)
			{
				KLog::Log("[ERROR] Children inited before.");
				return false;
			}

			m_pChildren.clear();
			for (auto& pAABB : pAABBVec)
			{
				m_pChildren.push_back(KSPtr<KOcTree>(new KOcTree(this, *pAABB, nullptr)));
			}

			m_eType = ETT_CUSTOM;

			return true;
		}

		bool _createSubTreeAABB(unsigned index, AABBf& out)
		{
			if (index >= DefaultOcTreeSubTreeCount)
			{
				KLog::Log("[ERROR] Invalid index during create subTree AABB.");
				return false;
			}

			bool bPositiveX = (index & 0x4) > 0U;
			bool bPositiveY = (index & 0x2) > 0U;
			bool bPositiveZ = (index & 0x1) > 0U;

			float fsubTreeAABBRadius[3] =
			{
				(m_AABB.max.coord[0] - m_AABB.min.coord[0]) * 0.5f,
				(m_AABB.max.coord[1] - m_AABB.min.coord[1]) * 0.5f,
				(m_AABB.max.coord[2] - m_AABB.min.coord[2]) * 0.5f
			};

			Point3Df subTreeAABBMin =
			{
				(bPositiveX) ? m_AABB.min.coord[0] + fsubTreeAABBRadius[0] : m_AABB.min.coord[0],
				(bPositiveY) ? m_AABB.min.coord[1] + fsubTreeAABBRadius[1] : m_AABB.min.coord[1],
				(bPositiveZ) ? m_AABB.min.coord[2] + fsubTreeAABBRadius[2] : m_AABB.min.coord[2],
			};

			Point3Df subTreeAABBMax =
			{
				(bPositiveX) ? m_AABB.max.coord[0] : m_AABB.max.coord[0] - fsubTreeAABBRadius[0],
				(bPositiveY) ? m_AABB.max.coord[1] : m_AABB.max.coord[1] - fsubTreeAABBRadius[1],
				(bPositiveZ) ? m_AABB.max.coord[2] : m_AABB.max.coord[2] - fsubTreeAABBRadius[2],
			};

			out = AABBf(subTreeAABBMin, subTreeAABBMax);

			return true;
		}

		bool _initSubTree()
		{
			if (m_eType != ETT_UNKNOWN)
			{
				KLog::Log("[ERROR] Children inited before.");
				return false;
			}

			m_pChildren.reserve(DefaultOcTreeSubTreeCount);

			for (unsigned i = 0; i < DefaultOcTreeSubTreeCount; i++)
			{
				AABBf aabb;
				auto pSubTreeAABB = _createSubTreeAABB(i, aabb);
				if (!pSubTreeAABB)
				{
					KLog::Log("[ERROR] Get subTree AABB failed.");
					return false;
				}

				m_pChildren.push_back(std::move(KSPtr<KOcTree>(new KOcTree(this, aabb))));
			}

			m_eType = ETT_DEFAULT;

			return true;
		}

		inline unsigned _getSubTreeIndex(const KSPtr<IOcTreeNode>& pNode)
		{
			if (m_eType == ETT_UNKNOWN)
			{
				throw "Exception";
				return UINT_MAX;
			}

			if (m_eType == ETT_DEFAULT)
			{
				// Default type can find index fast.
				auto& center = m_AABB.GetCenter();
				auto& nodeCoord = pNode->GetCoord();

				bool bOffsetX = nodeCoord.coord[0] > center.coord[0];
				bool bOffsetY = nodeCoord.coord[1] > center.coord[1];
				bool bOffsetZ = nodeCoord.coord[2] > center.coord[2];

				auto index = bOffsetX << 2 | bOffsetY << 1 | bOffsetZ;

				return index;
			}

			// Custom type
			for (unsigned i = m_pChildren.size() - 1; i >= 0; i--)
			{
				if (m_pChildren[i]->m_AABB.Inside(pNode->GetCoord()))
				{
					return i;
				} 
			}

			KLog::Log("[ERROR] Can not get sub tree index.");
			return UINT_MAX;
		}

		bool _addNodeToSubTree(const KSPtr<IOcTreeNode>& pNode, unsigned uSubTreeIndex)
		{
			if (!m_pChildren[uSubTreeIndex])
			{
// 				auto pSubTreeAABB = _createSubTreeAABB(uSubTreeIndex);
// 				if (!pSubTreeAABB)
// 				{
// 					KLog::Log("[ERROR] Get subTree AABB failed.");
// 					return false;
// 				}

				AABBf aabb;
				_createSubTreeAABB(uSubTreeIndex, aabb);

				m_pChildren[uSubTreeIndex].reset(new KOcTree(this, aabb, pNode));
				return true;
			}

			return m_pChildren[uSubTreeIndex]->_addNode(pNode);
		}

		KOcTree* m_pParent;
		std::vector<KSPtr<KOcTree>> m_pChildren;
		KSPtr<IOcTreeNode> m_pNodeData;
		const AABBf m_AABB;
		unsigned m_uNodeCount;
		ETreeType m_eType;
	};

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

					_min[0] = (i == -1) ? MergeAABB.min.coord[0] : ((i == 0) ? baseAABB.min.coord[0] : baseAABB.max.coord[0]);
					_min[1] = (j == -1) ? MergeAABB.min.coord[1] : ((j == 0) ? baseAABB.min.coord[1] : baseAABB.max.coord[1]);
					_min[2] = (k == -1) ? MergeAABB.min.coord[2] : ((k == 0) ? baseAABB.min.coord[2] : baseAABB.max.coord[2]);

					_max[0] = (i == -1) ? baseAABB.min.coord[0] : ((i == 0) ? baseAABB.max.coord[0] : MergeAABB.max.coord[0]);
					_max[1] = (j == -1) ? baseAABB.min.coord[1] : ((j == 0) ? baseAABB.max.coord[1] : MergeAABB.max.coord[1]);
					_max[2] = (k == -1) ? baseAABB.min.coord[2] : ((k == 0) ? baseAABB.max.coord[2] : MergeAABB.max.coord[2]);

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