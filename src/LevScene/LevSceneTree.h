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
		class LevSetObjModifiedVisitor;

		class LevSceneTree
		{
		public:
			LevSceneTree();
			bool AddNodeToRoot(LPtr<LevSceneNode> pNode, LPtr<LevSceneNode> pParentNode = nullptr);
			bool ResetObjUnModified();
			bool SetObjModified();
			bool UpdateWorldCoord();
			LevSceneNode& GetRoot();
			const LevSceneNode& GetRoot() const;

			void UpdateNodeState();

		private:
			void _checkDeleteNode(LevSceneNode& pBeginNode);

			LPtr<LevResetObjModifiedVisitor> m_modified_resetor;
			LPtr<LevStateUpdaterVisitor> m_state_updater;
			LPtr<LevCalculateWorldCoordVisitor> m_worldCoord_updater;
			LPtr<LevSetObjModifiedVisitor> m_modified_setor;
			LPtr<LevSceneNode> m_root;
		};
	}
}