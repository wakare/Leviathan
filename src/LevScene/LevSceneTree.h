#pragma once

#include <vector>
#include "LPtr.h"

namespace Leviathan
{
	namespace Scene
	{
		class LevSceneNode;
		class LevSceneObject;
		class LevResetObjModifiedVisitor;

		class LevSceneTree
		{
		public:
			LevSceneTree();
			bool AddNodeToRoot(LPtr<LevSceneNode> pNode, LPtr<LevSceneNode> pParentNode = nullptr);
			bool ResetObjModifiedState();

			LevSceneNode& GetRoot();
			const LevSceneNode& GetRoot() const;

		private:
			LPtr<LevResetObjModifiedVisitor> m_resetor;
			LPtr<LevSceneNode> m_root;
		};
	}
}