#pragma once
#include <vector>
#include <memory>
#include "ISpaceAccStruct.h"

namespace Leviathan
{
	namespace SpaceAccStruct
	{ 
		template <typename scalar>
		struct TreeNode
		{
			static unsigned maxDepth;

			AABB<scalar> aabb;
			unsigned uDepth;
			std::vector<unsigned> dataVec;
			std::unique_ptr<TreeNode> children[8];
			
			TreeNode(const AABB<scalar>& _aabb, unsigned depth);
			bool IsLeaf() const;
			bool RayIntersect(float* rayPos, float* rayDir, float& distance) const;
			TreeNode<scalar>& getOcCreateSubTree(unsigned index);
		};

		typedef unsigned DataHandle;

		template<typename scalar>
		class OcTreeAccStruct : public ISpaceAccStruct<scalar>
		{
		public:
			OcTreeAccStruct();
			virtual void AddNode(const AABB<scalar>& node);
			virtual const AABB<scalar>& Pick(float* rayPos, float* rayDir);

		private:
			void _addData(TreeNode<scalar>& begin, const AABB<scalar>& aabb, unsigned index);
			void _intersect(TreeNode<scalar>* pBegin, float* rayPos, float* rayDir, float& minDistance, std::vector<TreeNode<scalar>*>& pResult);
			std::vector<const AABB<scalar>*> data;
			std::unique_ptr<TreeNode<scalar>> m_pRoot;
		};

		
	}
}

#include "OcTreeAccStruct.hpp"