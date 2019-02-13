#pragma once
#include "OcTreeAccStruct.h"

namespace Leviathan
{
	namespace SpaceAccStruct
	{
		template <typename scalar>
		Leviathan::SpaceAccStruct::TreeNode<scalar>::TreeNode(const AABB<scalar>& _aabb, unsigned depth) :
			aabb(_aabb), uDepth(depth)
		{
		}

		template <typename scalar>
		bool Leviathan::SpaceAccStruct::TreeNode<scalar>::IsLeaf() const
		{
			return uDepth >= maxDepth;
		}

		template <typename scalar>
		bool Leviathan::SpaceAccStruct::TreeNode<scalar>::RayIntersect(float* rayPos, float* rayDir, float& distance) const
		{
			return aabb.RayIntersect(rayPos, rayDir, distance);
		}

		template <typename scalar>
		TreeNode<scalar>& TreeNode<scalar>::getOcCreateSubTree(unsigned index)
		{
			if (!children[index])
			{
				float* center = aabb.center;
				bool bPositiveX = index & 0x4;
				bool bPositiveY = index & 0x2;
				bool bPositiveZ = index & 0x1;
				float tempCoord[3] =
				{
					(bPositiveX) ? aabb.max[0] : aabb.min[0],
					(bPositiveY) ? aabb.max[1] : aabb.min[1],
					(bPositiveZ) ? aabb.max[2] : aabb.min[2]
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

		template<typename scalar>
		OcTreeAccStruct<scalar>::OcTreeAccStruct()
		{

		}

		template<typename scalar>
		void OcTreeAccStruct<scalar>::AddNode(const AABB<scalar>& node)
		{
			if (!AABBInside(m_pRoot->aabb, aabb))
			{
				throw "exception";
				return;
			}

			data.push_back(&node);
			unsigned index = data.size();

			_addData(*m_pRoot, aabb, index - 1);
		}

		template<typename scalar>
		void OcTreeAccStruct<scalar>::_intersect(TreeNode<scalar>* pBegin, float* rayPos, float* rayDir, float& minDistance, std::vector<TreeNode<scalar>*>& pResult)
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

		template <typename scalar>
		const AABB<scalar>& OcTreeAccStruct<scalar>::Pick(float* rayPos, float* rayDir)
		{
			float minDistance = -1.0f;
			std::vector<TreeNode<scalar>*> pResultVec;
			const AABB<scalar>* pResult;

			_intersect(m_pRoot.get(), rayPos, rayDir, minDistance, pResultVec);
			for (auto result : pResultVec)
			{
				float minDistance = FLT_MAX;
				for (auto index : result->dataVec)
				{
					auto& _data = data[index];
					
					float _distance = -1.0f;
					if (_data.RayIntersect(rayPos, rayDir, _distance))
					{
						if (_distance < minDistance)
						{
							minDistance = _distance;
							pResult = _data;
						}
					}
				}
			}

			return *pResult;
		}

		template<typename scalar>
		void Leviathan::SpaceAccStruct::OcTreeAccStruct<scalar>::_addData(TreeNode<scalar>& begin, const AABB<scalar>& aabb, unsigned index)
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

	}
}

