#pragma once

#include <functional>
#include <vector>
#include "NodeVisitor.h"
#include "LevSceneAPIDefine.h"

namespace Leviathan
{
	template <typename T>
	class Node;

	namespace Scene
	{
		class LevSceneObject;

		class LEV_SCENE_API  LevSceneTreeSearchVisitor : public NodeVisitor<LevSceneObject>
		{
		public:
			// Callback parameters:
			//			param0 : traversed object
			//			param1 : traverse stack
			//			param2 : stop this search
			//			return value : need traverse children node
			typedef std::function<bool(const LevSceneObject&, const std::vector<const Node<LevSceneObject>*>&, bool&)> LevSearchCallback;

			LevSceneTreeSearchVisitor(LevSearchCallback searchFunc = nullptr);
			void SetTraverseCallback(LevSearchCallback searchFunc);

			void Apply(Node<LevSceneObject>& node);
			void Apply(const Node<LevSceneObject>& node);

		private:
			bool m_stopSearch;
			std::vector<const Node<LevSceneObject>*> m_traverseStack;
			LevSearchCallback m_searchFunc;
		};
	}
}