#pragma once
#include <memory>
#include <vector>
#include "KLog.h" 
#include "LPtr.h"
#include <functional>

namespace Leviathan
{
	#define KUPtr std::unique_ptr
	#define KSPtr Leviathan::LPtr
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
		Point3Df m_max;
		Point3Df m_min;

		Point3Df GetCenter() const
		{
			float center[3] =
			{
				(m_min.coord[0] + m_max.coord[0]) * 0.5f,
				(m_min.coord[1] + m_max.coord[1]) * 0.5f,
				(m_min.coord[2] + m_max.coord[2]) * 0.5f
			};

			return center;
		}

		float GetRadius() const
		{
			auto center = GetCenter();
			return Point3Df::Distance(center, m_min);
		}

		bool Inside(const Point3Df& rhs) const
		{
			return	(rhs.coord[0] <= m_max.coord[0] && rhs.coord[0] >= m_min.coord[0]) &&
					(rhs.coord[1] <= m_max.coord[1] && rhs.coord[1] >= m_min.coord[1]) && 
					(rhs.coord[2] <= m_max.coord[2] && rhs.coord[2] >= m_min.coord[2]);
		}

		bool Inside(const AABBf& rhs) const 
		{
			/*return (min <= rhs.min && rhs.max <= max);*/
			bool bMin =
				m_min.coord[0] <= rhs.m_min.coord[0] &&
				m_min.coord[1] <= rhs.m_min.coord[1] &&
				m_min.coord[2] <= rhs.m_min.coord[2];
			if (!bMin)
			{
				return false;
			}

			bool bMax =
				m_max.coord[0] >= rhs.m_max.coord[0] &&
				m_max.coord[1] >= rhs.m_max.coord[1] &&
				m_max.coord[2] >= rhs.m_max.coord[2];

			return bMax;
		}

		AABBf Merge(const AABBf& rhs) const 
		{
			float _min[3];
			float _max[3];

			_min[0] = fmin(m_min.coord[0], rhs.m_min.coord[0]);
			_min[1] = fmin(m_min.coord[1], rhs.m_min.coord[1]);
			_min[2] = fmin(m_min.coord[2], rhs.m_min.coord[2]);

			_max[0] = fmax(m_max.coord[0], rhs.m_max.coord[0]);
			_max[1] = fmax(m_max.coord[1], rhs.m_max.coord[1]);
			_max[2] = fmax(m_max.coord[2], rhs.m_max.coord[2]);

			return AABBf(_min, _max);
		}

		AABBf()
		{
		}

		AABBf(const Point3Df& _min, const Point3Df& _max):
			m_min(_min), 
			m_max(_max)
		{
		}
	};

	class IOcTreeNode
	{
	public:
		IOcTreeNode(const Point3Df& rhs); 
		bool operator< (const IOcTreeNode& rhs) const;
		bool operator<= (const IOcTreeNode& rhs) const;
		const Point3Df& GetCoord() const;
		std::string ToString() const;
		virtual ~IOcTreeNode();
	private:
		Point3Df m_coord;
	};

	class KOcTree
	{
	public:
		typedef std::function<void(KOcTree& rhs)> TraverseFunction;
		typedef std::function<void(const KOcTree& rhs)> ConstTraverseFunction;

		enum ETreeType
		{
			ETT_DEFAULT_ONE			= 1,		// 8-subTree
			ETT_DEFAULT_SECOND		= 1 << 1,	// 27-subTree
			ETT_NON_LEAF			= 1 << 2,
			ETT_CUSTOM				= 1 << 3,
			ETT_UNKNOWN				= 1 << 4,
		};

		KOcTree(KOcTree* pParent, const AABBf& AABB);
		~KOcTree();

		bool IsLeaf() const;
		std::vector<KSPtr<IOcTreeNode>> GetLeafNodeVec() const;

		bool IsRoot() const;
		unsigned GetAddedNodeCount() const;
		const AABBf& GetAABB() const;
		
		const KOcTree* const GetParent() const;
		const std::vector<KUPtr<KOcTree>>& GetChildren() const;
		void Traverse(TraverseFunction& traverseFunc, bool bRecursion);
		void ConstTraverse(ConstTraverseFunction& traverseFunc, bool bRecursion) const;
		bool ReConstructAverageOcTree(KUPtr<KOcTree>&& outResult);
		static void SetMaxLeafNodeCount(unsigned uMax);

		friend KUPtr<KOcTree> CreateParentOcTreeByChild(KUPtr<AABBf>&& pAABB, KUPtr<KOcTree>&& pChild);
		friend KUPtr<KOcTree> AddNodeAndUpdateOcTree(KUPtr<KOcTree> pOcTree, std::vector<KSPtr<IOcTreeNode>>& needAddNodeVec);

		std::vector<KSPtr<IOcTreeNode>> SearchRadiusNodeSet(KUPtr<IOcTreeNode> pNode, float fSearchRadius);

		// TODO: Implement
		std::vector<KUPtr<IOcTreeNode>> SearchNearestNodeSet(KUPtr<IOcTreeNode> pNode, unsigned uMaxSearchCount);

	private:
		bool _setParent(KOcTree* pParent);
		bool _addNode(KSPtr<IOcTreeNode>&& pNode);
		bool _addNode(std::vector<KSPtr<IOcTreeNode>>& pNodeVec);
		bool _addChildOcTree(KUPtr<KOcTree>&& pOcTree);
		bool _initChildrenByAABBVec(KUPtr<KOcTree>&& pChild);
		bool _createDefaultSubTreeAABB(unsigned index, AABBf& out) const;
		bool _createSlicedSubTreeAABB(unsigned index, AABBf& out) const;
		bool _initDefaultSubTree();
		bool _addNodeToSubTree(KSPtr<IOcTreeNode>& pNode, unsigned uSubTreeIndex);
		unsigned _getSubTreeIndex(const KSPtr<IOcTreeNode>& pNode) const;

		KOcTree* m_pParent;
		std::vector<KUPtr<KOcTree>> m_pChildrenVec;
		std::vector<KSPtr<IOcTreeNode>> m_pNodeDataVec;
		const AABBf m_AABB;
		unsigned m_uAddedNodeCount;	
		int m_eType;
		static unsigned uMaxLeafNodeCount;
	};
}