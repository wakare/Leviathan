#pragma once

#include <vector>
#include "LSPtr.h"
#include "LevSceneAPIDefine.h"

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
		class LevTimerTickVisitor;

		class LEV_SCENE_API LevSceneTree
		{
		public:
			LevSceneTree();
			bool AddNodeToParent(LSPtr<LevSceneNode> pNode, LSPtr<LevSceneNode> pParentNode = nullptr);
			bool ResetObjUnModified();
			bool SetObjModified();
			bool UpdateWorldCoord();
			bool UpdateTimer();
			LevSceneNode& GetRoot();
			const LevSceneNode& GetRoot() const;

			void UpdateNodeState();

		private:
			void _checkDeleteNode(LevSceneNode& pBeginNode);

			LSPtr<LevResetObjModifiedVisitor> m_modified_resetor;
			LSPtr<LevStateUpdaterVisitor> m_state_updater;
			LSPtr<LevCalculateWorldCoordVisitor> m_worldCoord_updater;
			LSPtr<LevSetObjModifiedVisitor> m_modified_setor;
			LSPtr<LevTimerTickVisitor> m_time_ticker;
			LSPtr<LevSceneNode> m_root;
		};
	}
}