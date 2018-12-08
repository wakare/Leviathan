#include "KOcTree.h"
#include <string>

unsigned Leviathan::KOcTree::uMaxLeafNodeCount = 10;

Leviathan::IOcTreeNode::IOcTreeNode(const Point3Df& rhs) :
	m_coord(rhs)
{

}

bool Leviathan::IOcTreeNode::operator<(const IOcTreeNode& rhs) const
{
	return m_coord < rhs.m_coord;
}

const Leviathan::Point3Df& Leviathan::IOcTreeNode::GetCoord() const
{
	return m_coord;
}

// Only for debug
std::string Leviathan::IOcTreeNode::ToString() const
{
	char buff[100];
	snprintf(buff, sizeof(buff), " %f %f %f", m_coord.coord[0], m_coord.coord[1], m_coord.coord[2]);
	return buff;
}

Leviathan::IOcTreeNode::~IOcTreeNode()
{

}

bool Leviathan::IOcTreeNode::operator<=(const IOcTreeNode& rhs) const
{
	return m_coord <= rhs.m_coord;
}

Leviathan::KOcTree::KOcTree(KOcTree* pParent, const AABBf& AABB) :
	m_pParent(pParent),
	m_AABB(AABB),
	m_uAddedNodeCount(0),
	m_eType(ETT_UNKNOWN)
{
}

Leviathan::KOcTree::~KOcTree()
{
}

bool Leviathan::KOcTree::IsLeaf() const
{
	return m_pNodeDataVec.size() <= KOcTree::uMaxLeafNodeCount && !(m_eType & ETT_NON_LEAF);
}

std::vector<KSPtr<Leviathan::IOcTreeNode>> Leviathan::KOcTree::GetLeafNodeVec() const
{
	return m_pNodeDataVec;
}

bool Leviathan::KOcTree::IsRoot() const
{
	return m_pParent == nullptr;
}

unsigned Leviathan::KOcTree::GetAddedNodeCount() const
{
	return m_uAddedNodeCount;
}

const Leviathan::AABBf& Leviathan::KOcTree::GetAABB() const
{
	return m_AABB;
}

bool Leviathan::KOcTree::_setParent(KOcTree* pParent)
{
	if (!pParent)
	{
		return false;
	}

	m_pParent = pParent;
	return true;
}

const Leviathan::KOcTree* const Leviathan::KOcTree::GetParent() const
{
	return m_pParent;
}

const std::vector<KUPtr<Leviathan::KOcTree>>& Leviathan::KOcTree::GetChildren() const
{
	return m_pChildrenVec;
}

void Leviathan::KOcTree::Traverse(Leviathan::KOcTree::TraverseFunction& traverseFunc, bool bRecursion)
{
	for (auto& child : m_pChildrenVec)
	{
		if (!child)
		{
			continue;
		}

		traverseFunc(*child);
		if (bRecursion)
		{
			child->Traverse(traverseFunc, bRecursion);
		}
	}
}

void Leviathan::KOcTree::ConstTraverse(ConstTraverseFunction& traverseFunc, bool bRecursion) const
{
	for (const auto& child : m_pChildrenVec)
	{
		if (!child)
		{
			continue;
		}

		traverseFunc(*child);
		if (bRecursion)
		{
			child->ConstTraverse(traverseFunc, bRecursion);
		}
	}
}

bool Leviathan::KOcTree::ReConstructAverageOcTree(KUPtr<KOcTree>&& outResult)
{
	if (outResult.get() == this)
	{
		KLog::Log("[ERROR] Invalid out result.");
		return false;
	}

	outResult.reset(new KOcTree(m_pParent, m_AABB));
	TraverseFunction traverseFunc = [&outResult](KOcTree& rhs)
	{ 
		// TODO: This place use KSPTR
		if (rhs.IsLeaf())
		{
			for (auto& pNode : rhs.GetLeafNodeVec())
			{
				outResult->_addNode(std::move(pNode));
			}
		}
	};

	// Traverse all leaf node
	Traverse(traverseFunc, true);

	return true;
}

void Leviathan::KOcTree::SetMaxLeafNodeCount(unsigned uMax)
{
	Leviathan::KOcTree::uMaxLeafNodeCount = uMax;
}

std::vector<KSPtr<Leviathan::IOcTreeNode>> Leviathan::KOcTree::SearchRadiusNodeSet(KUPtr<IOcTreeNode> pNode, float fSearchRadius)
{
	std::vector<KSPtr<IOcTreeNode>> result;
	auto coord = pNode->GetCoord();

	TraverseFunction traverseFunc = [&result, &coord, fSearchRadius](KOcTree& rhs)
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
			auto pLeafNodeVec = rhs.GetLeafNodeVec();
			for (auto& pNode : pLeafNodeVec)
			{
				auto leafCoord = pNode->GetCoord();
				auto fDistance = Point3Df::Distance(coord, leafCoord);

				if (fDistance < fSearchRadius)
				{
					result.push_back(std::move(pNode));
				}
			}
		}
	};

	Traverse(traverseFunc, true);

	return result;
}

bool Leviathan::KOcTree::_addNode(KSPtr<IOcTreeNode>&& pNode)
{
	m_uAddedNodeCount++;

	if (m_uAddedNodeCount <= KOcTree::uMaxLeafNodeCount)
	{
		m_pNodeDataVec.push_back(std::move(pNode));
		return true;
	}

	if (!(m_eType & ETT_NON_LEAF))
	{
		if (m_eType & ETT_UNKNOWN && !_initDefaultSubTree())
		{
			KLog::Log("[ERROR] Init subTree failed.");
			return false;
		}

		for (auto pNode : m_pNodeDataVec)
		{
			auto _index = _getSubTreeIndex(pNode);
			if (!_addNodeToSubTree(pNode, _index))
			{
				return false;
			}	
		}

		m_pNodeDataVec.clear();

		// Non-leaf flag set
		m_eType |= ETT_NON_LEAF;
	}

	auto index = _getSubTreeIndex(pNode);
	if (!_addNodeToSubTree(pNode, index))
	{
		return false;
	}

	return true;
}

bool Leviathan::KOcTree::_addChildOcTree(KUPtr<KOcTree>&& pOcTree)
{
	m_uAddedNodeCount += pOcTree->m_uAddedNodeCount;
	m_pChildrenVec.push_back(std::move(pOcTree));
	
	return true;
}

bool Leviathan::KOcTree::_initChildrenByAABBVec(KUPtr<KOcTree>&& pChild)
{
	if (!m_eType & ETT_UNKNOWN)
	{
		KLog::Log("[ERROR] Children inited before.");
		return false;
	}

	m_pChildrenVec.clear();
	m_pChildrenVec.resize(26);
	m_uAddedNodeCount += pChild->m_uAddedNodeCount;
	m_pChildrenVec.insert(m_pChildrenVec.begin() + 13, std::move(pChild));
	
	m_eType &= !(m_eType & ETT_UNKNOWN);
	m_eType |= ETT_DEFAULT_SECOND;

	return true;
}

bool Leviathan::KOcTree::_createDefaultSubTreeAABB(unsigned index, AABBf& out) const
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
		(m_AABB.m_max.coord[0] - m_AABB.m_min.coord[0]) * 0.5f,
		(m_AABB.m_max.coord[1] - m_AABB.m_min.coord[1]) * 0.5f,
		(m_AABB.m_max.coord[2] - m_AABB.m_min.coord[2]) * 0.5f
	};

	Point3Df subTreeAABBMin =
	{
		(bPositiveX) ? m_AABB.m_min.coord[0] + fsubTreeAABBRadius[0] : m_AABB.m_min.coord[0],
		(bPositiveY) ? m_AABB.m_min.coord[1] + fsubTreeAABBRadius[1] : m_AABB.m_min.coord[1],
		(bPositiveZ) ? m_AABB.m_min.coord[2] + fsubTreeAABBRadius[2] : m_AABB.m_min.coord[2],
	};

	Point3Df subTreeAABBMax =
	{
		(bPositiveX) ? m_AABB.m_max.coord[0] : m_AABB.m_max.coord[0] - fsubTreeAABBRadius[0],
		(bPositiveY) ? m_AABB.m_max.coord[1] : m_AABB.m_max.coord[1] - fsubTreeAABBRadius[1],
		(bPositiveZ) ? m_AABB.m_max.coord[2] : m_AABB.m_max.coord[2] - fsubTreeAABBRadius[2],
	};

	out = AABBf(subTreeAABBMin, subTreeAABBMax);

	return true;
}

bool Leviathan::KOcTree::_createSlicedSubTreeAABB(unsigned index, AABBf& out) const
{
	unsigned xOffset = index / 9;
	unsigned yOffset = (index - 9 * xOffset) / 3;
	unsigned zOffset = index - 9 * xOffset - 3 * yOffset;

	float _min[3];
	float _max[3];

	auto& baseAABB = m_pChildrenVec[13]->GetAABB();
	auto& MergeAABB = m_AABB;

	_min[0] = (xOffset == 0) ? MergeAABB.m_min.coord[0] : ((xOffset == 1) ? baseAABB.m_min.coord[0] : baseAABB.m_max.coord[0]);
	_min[1] = (yOffset == 0) ? MergeAABB.m_min.coord[1] : ((yOffset == 1) ? baseAABB.m_min.coord[1] : baseAABB.m_max.coord[1]);
	_min[2] = (zOffset == 0) ? MergeAABB.m_min.coord[2] : ((zOffset == 1) ? baseAABB.m_min.coord[2] : baseAABB.m_max.coord[2]);

	_max[0] = (xOffset == 0) ? baseAABB.m_min.coord[0] : ((xOffset == 1) ? baseAABB.m_max.coord[0] : MergeAABB.m_max.coord[0]);
	_max[1] = (yOffset == 0) ? baseAABB.m_min.coord[1] : ((yOffset == 1) ? baseAABB.m_max.coord[1] : MergeAABB.m_max.coord[1]);
	_max[2] = (zOffset == 0) ? baseAABB.m_min.coord[2] : ((zOffset == 1) ? baseAABB.m_max.coord[2] : MergeAABB.m_max.coord[2]);

	out = AABBf(_min, _max);
	return true;
}

bool Leviathan::KOcTree::_initDefaultSubTree()
{
	if (!m_eType & ETT_UNKNOWN)
	{
		KLog::Log("[ERROR] Children inited before.");
		return false;
	}

	m_pChildrenVec.resize(DefaultOcTreeSubTreeCount);
	m_eType &= !(m_eType & ETT_UNKNOWN);
	m_eType |= ETT_DEFAULT_ONE;

	return true;
}

unsigned Leviathan::KOcTree::_getSubTreeIndex(const KSPtr<IOcTreeNode>& pNode) const 
{
	if (m_eType & ETT_UNKNOWN)
	{
		throw "Exception";
		return UINT_MAX;
	}

	if (m_eType & ETT_DEFAULT_ONE)
	{
		// Default type can find index fast.
		auto center = m_AABB.GetCenter();
		auto& nodeCoord = pNode->GetCoord();

		unsigned bOffsetX = nodeCoord.coord[0] > center.coord[0] ? 1 : 0;
		unsigned bOffsetY = nodeCoord.coord[1] > center.coord[1] ? 1 : 0;
		unsigned bOffsetZ = nodeCoord.coord[2] > center.coord[2] ? 1 : 0;

		return bOffsetX << 2 | bOffsetY << 1 | bOffsetZ;
	}

	if (m_eType & ETT_DEFAULT_SECOND)
	{
		// Get center AABB coord
		if (m_pChildrenVec.size() != 27)
		{
			throw "Exception";
		}
	
		auto& nodeCoord = pNode->GetCoord();
		auto& centerAABB = m_pChildrenVec[13]->GetAABB();

		unsigned xOffset = nodeCoord.coord[0] < centerAABB.m_min.coord[0] ? 0 : (nodeCoord.coord[0] < centerAABB.m_max.coord[0] ? 1 : 2);
		unsigned yOffset = nodeCoord.coord[1] < centerAABB.m_min.coord[1] ? 0 : (nodeCoord.coord[1] < centerAABB.m_max.coord[1] ? 1 : 2);
		unsigned zOffset = nodeCoord.coord[2] < centerAABB.m_min.coord[2] ? 0 : (nodeCoord.coord[2] < centerAABB.m_max.coord[2] ? 1 : 2);
	
		return xOffset * 9 + yOffset * 3 + zOffset;
	}

	// Custom type
	for (unsigned i = 0 ; i < m_pChildrenVec.size(); i++)
	{
		if (!m_pChildrenVec[i])
		{
			continue;
		}

		if (m_pChildrenVec[i]->m_AABB.Inside(pNode->GetCoord()))
		{
			return i;
		}
	}

	KLog::Log("[ERROR] Can not get sub tree index.");
	return UINT_MAX;
}

bool Leviathan::KOcTree::_addNodeToSubTree(KSPtr<IOcTreeNode>& pNode, unsigned uSubTreeIndex)
{
	if (!m_pChildrenVec[uSubTreeIndex])
	{
		AABBf aabb;

		if (m_eType & ETT_DEFAULT_ONE)
		{
			_createDefaultSubTreeAABB(uSubTreeIndex, aabb);
		}
		else if (m_eType & ETT_DEFAULT_SECOND)
		{
			_createSlicedSubTreeAABB(uSubTreeIndex, aabb);
		}
		else
		{
			throw "Exception";
		}

		m_pChildrenVec[uSubTreeIndex].reset(new KOcTree(this, aabb));
	}

	return m_pChildrenVec[uSubTreeIndex]->_addNode(std::move(pNode));
}

bool Leviathan::KOcTree::_addNode(std::vector<KSPtr<IOcTreeNode>>& pNodeVec)
{
	for (auto& pNode : pNodeVec)
	{
		if (!_addNode(std::move(pNode)))
		{
			return false;
		}
	}

	// Can not use vector element before std::move
	pNodeVec.clear();

	return true;
}

KUPtr<Leviathan::KOcTree> Leviathan::CreateParentOcTreeByChild(KUPtr<AABBf>&& pAABB, KUPtr<KOcTree>&& pChild)
{
	if (pChild->GetAABB().Inside(*pAABB))
	{
		//KLog::Log("[INFO] No need create new OcTree.");
		return std::move(pChild);
	}

	AABBf MergeAABB = pAABB->Merge(pChild->GetAABB());

	KUPtr<KOcTree> result(new KOcTree(nullptr, MergeAABB));
	if (!result)
	{
		KLog::Log("[ERROR] Create OcTree failed.");
		return std::move(pChild);
	}

	if (!result->_initChildrenByAABBVec(std::move(pChild)))
	{
		KLog::Log("[ERROR] Init children AABB failed.");
		return std::move(pChild);
	}

	return std::move(result);
};

KUPtr<Leviathan::KOcTree> Leviathan::AddNodeAndUpdateOcTree(KUPtr<KOcTree> pOcTree, std::vector<KSPtr<IOcTreeNode>>& needAddNodeVec)
{
	if (!pOcTree)
	{
		return pOcTree;
	}

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

	KUPtr<AABBf> pAABB;
	pAABB.reset(new AABBf(min, max));
	auto pResult = CreateParentOcTreeByChild(std::move(pAABB), std::move(pOcTree));

	if (!pResult->_addNode(needAddNodeVec))
	{
		KLog::Log("[ERROR] Add node failed.");
		throw "Exception";
	}

	return pResult;
}
