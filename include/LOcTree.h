#pragma once
#include <memory>
#include <vector>
#include <functional>
#include "AABB.h"

namespace Leviathan
{
	struct TreeNode
	{
		AABB aabb;
		unsigned uDepth;
		std::vector<unsigned> dataVec;
		std::unique_ptr<TreeNode> children[8];
		
		static unsigned maxDepth;

		TreeNode(const AABB& _aabb, unsigned depth):
			aabb(_aabb), uDepth(depth)
		{
		}

		bool IsLeaf() const
		{
			return uDepth >= maxDepth;
		}

		bool RayIntersect(float* rayPos, float* rayDir, float& distance) const
		{
			if (AABBInside(aabb, AABB(rayPos, rayPos)))
			{
				distance = 0.0f;
				return true;
			}

			static auto swap = [](float& a, float& b)
			{
				float temp = a;
				a = b;
				b = temp;
			};

			distance = -1.0f;
			float tmin = (aabb.Min()[0] - rayPos[0]) / rayDir[0];
			float tmax = (aabb.Max()[0] - rayPos[0]) / rayDir[0];

			if (tmin > tmax) swap(tmin, tmax);

			float tymin = (aabb.Min()[1] - rayPos[1]) / rayDir[1];
			float tymax = (aabb.Max()[1] - rayPos[1]) / rayDir[1];

			if (tymin > tymax) swap(tymin, tymax);

			if ((tmin > tymax) || (tymin > tmax))
				return false;

			if (tymin > tmin)
				tmin = tymin;

			if (tymax < tmax)
				tmax = tymax;

			float tzmin = (aabb.Min()[2] - rayPos[2]) / rayDir[2];
			float tzmax = (aabb.Max()[2] - rayPos[2]) / rayDir[2];

			if (tzmin > tzmax) swap(tzmin, tzmax);

			if ((tmin > tzmax) || (tzmin > tmax))
				return false;

			if (tzmin > tmin)
				tmin = tzmin;

			if (tzmax < tmax)
				tmax = tzmax;

			distance = tmin;
			return true;
		}

		TreeNode& getOcCreateSubTree(unsigned index)
		{
			if (!children[index])
			{
				const float* center = aabb.Center();
				bool bPositiveX = index & 0x4;
				bool bPositiveY = index & 0x2;
				bool bPositiveZ = index & 0x1;
				float tempCoord[3] =
				{
					(bPositiveX) ? aabb.Max()[0] : aabb.Min()[0],
					(bPositiveY) ? aabb.Max()[1] : aabb.Min()[1],
					(bPositiveZ) ? aabb.Max()[2] : aabb.Min()[2]
				};

				float min[3] =
				{
					fmin(tempCoord[0], center[0]),
					fmin(tempCoord[1], center[1]),
					fmin(tempCoord[2], center[2]),
				};

				float max[3] =
				{
					fmax(tempCoord[0], center[0]),
					fmax(tempCoord[1], center[1]),
					fmax(tempCoord[2], center[2]),
				};

				children[index].reset(new TreeNode(AABB(min, max), uDepth + 1));
			}

			return *children[index];
		}
	};

	template<typename T>
	class LOcTree
	{
	public:
		LOcTree(const AABB& range) 
		{
			m_pRoot.reset(new TreeNode(range, 0));
		};

		void AddData(T* pNode, const AABB& aabb);
		const AABB& GetAABB() const;
		bool RayIntersect(float* rayPos, float* rayDir, std::vector<TreeNode*>& pIntersect);
		void Traverse(std::function<void(T&)> callback, bool recursion);
		const std::vector<T*>& GetDataVec() const;
	private:
		void _traverse(TreeNode& begin, std::function<void(T&)> callback, bool recursion);
		void _addData(TreeNode& begin, const AABB& aabb, unsigned index);
		void _intersect(TreeNode* pBegin, float* rayPos, float* rayDir, float& minDistance, std::vector<TreeNode*>& pResult);
		std::vector<T*> m_dataVec;
		std::unique_ptr<TreeNode> m_pRoot;
	};

	template<typename T>
	void Leviathan::LOcTree<T>::Traverse(std::function<void(T&)> callback, bool recursion)
	{
		_traverse(*m_pRoot, callback, recursion);
	}

	template<typename T>
	const AABB& Leviathan::LOcTree<T>::GetAABB() const
	{
		return m_pRoot->aabb;
	}

	template<typename T>
	const std::vector<T*>& Leviathan::LOcTree<T>::GetDataVec() const
	{
		return m_dataVec;
	}

	template<typename T>
	void Leviathan::LOcTree<T>::_intersect(TreeNode* pBegin, float* rayPos, float* rayDir, float& minDistance, std::vector<TreeNode*>& pResult)
	{
		float _distance;
		if (!pBegin->RayIntersect(rayPos, rayDir, _distance)) return;
		
		if (pBegin->IsLeaf())
		{
			if (pBegin->dataVec.size() > 0/* && (minDistance < 0.0f || minDistance > _distance)*/)
			{
				//minDistance = _distance;
				pResult.push_back(pBegin);
			}

			return;
		}

		for (unsigned i = 0; i < 8; i++)
		{
			if (pBegin->children[i])
			{
				_intersect(pBegin->children[i].get(), rayPos, rayDir, minDistance, pResult);
			}
		}
	}

	template<typename T>
	inline bool Leviathan::LOcTree<T>::RayIntersect(float* rayPos, float* rayDir, std::vector<TreeNode*>& pIntersect)
	{
		float minDistance = -1.0f;
		std::vector<TreeNode*> pResultVec;
		_intersect(m_pRoot.get(), rayPos, rayDir, minDistance, pResultVec);
		pIntersect = pResultVec;

		return pIntersect.size();
	}

	template<typename T>
	inline void LOcTree<T>::_traverse(TreeNode& begin, std::function<void(T&)> callback, bool recursion)
	{
		for (auto dataIndex : begin.dataVec)
		{
			auto& pData = m_dataVec[dataIndex];
			callback(*pData);
		}

		if (recursion)
		{
			for (auto& child : begin.children)
			{
				_traverse(*child, callback, recursion);
			}
		}
	}

	template<typename T>
	inline void Leviathan::LOcTree<T>::_addData(TreeNode& begin, const AABB& aabb, unsigned index)
	{
		if (begin.IsLeaf())
		{
			begin.dataVec.push_back(index);
			return;
		}

		bool bAdded = false;

		// Add index to ocTree.
		std::vector<unsigned> intersectSubTreeIndex;

		for (unsigned i = 0; i < 8; i++)
		{
			auto& subTree = begin.getOcCreateSubTree(i);
			if (AABBInside(subTree.aabb, aabb) || AABBInside(aabb, subTree.aabb))
			{
				intersectSubTreeIndex.push_back(i);
			}
			else
			{
				if (AABBIntersect(subTree.aabb, aabb))
				{
					intersectSubTreeIndex.push_back(i);
				}
			}
		}

		for (auto _index : intersectSubTreeIndex)
		{
			_addData(begin.getOcCreateSubTree(_index), aabb, index);
			bAdded = true;
		}

		if (!bAdded)
		{
			throw "exception";
		}
	}

	template<typename T>
	inline void Leviathan::LOcTree<T>::AddData(T* pNode, const AABB& aabb)
	{
		if (!AABBInside(m_pRoot->aabb, aabb))
		{
			throw "exception";
			return;
		}

		m_dataVec.push_back(pNode);
		unsigned index = m_dataVec.size();

		_addData(*m_pRoot, aabb, index - 1);
	}

}