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
		class LevStateUpdaterVisitor;
		class LevCalculateWorldCoordVisitor;

		class LevSceneTree
		{
		public:
			LevSceneTree();
			bool AddNodeToRoot(LPtr<LevSceneNode> pNode, LPtr<LevSceneNode> pParentNode = nullptr);
			bool ResetObjUnModified();
			bool UpdateWorldCoord();
			LevSceneNode& GetRoot();
			const LevSceneNode& GetRoot() const;

			void Update();

		private:
			void _checkDeleteNode(LevSceneNode& pBeginNode);

			LPtr<LevResetObjModifiedVisitor> m_resetor;
			LPtr<LevStateUpdaterVisitor> m_state_updater;
			LPtr<LevCalculateWorldCoordVisitor> m_worldCoord_updater;
			LPtr<LevSceneNode> m_root;
		};
	}
}