#pragma once

#include <vector>
#include "LPtr.h"
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
			bool AddNodeToRoot(LPtr<LevSceneNode> pNode, LPtr<LevSceneNode> pParentNode = nullptr);
			bool ResetObjUnModified();
			bool SetObjModified();
			bool UpdateWorldCoord();
			bool UpdateTimer();
			LevSceneNode& GetRoot();
			const LevSceneNode& GetRoot() const;

			void UpdateNodeState();

		private:
			void _checkDeleteNode(LevSceneNode& pBeginNode);

			LPtr<LevResetObjModifiedVisitor> m_modified_resetor;
			LPtr<LevStateUpdaterVisitor> m_state_updater;
			LPtr<LevCalculateWorldCoordVisitor> m_worldCoord_updater;
			LPtr<LevSetObjModifiedVisitor> m_modified_setor;
			LPtr<LevTimerTickVisitor> m_time_ticker;
			LPtr<LevSceneNode> m_root;
		};
	}
}