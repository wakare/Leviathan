#pragma once

#include <vector>
#include <functional>
#include "NodeVisitor.h"
#include "LevSceneAPIDefine.h"

namespace Leviathan
{
	template <typename T>
	class Node;

	namespace Scene
	{
		class LevSceneObject;

		class LEV_SCENE_API LevSceneTreeTraverseVisitor : public NodeVisitor<LevSceneObject>
		{
		public:
			// Callback parameters:
			//			param0 : traversed object
			//			param1 : traverse stack
			//			return value : need traverse children node
			typedef std::function<bool(const LevSceneObject&, const std::vector<const Node<LevSceneObject>*>&)> LevTraverseCallback;
			LevSceneTreeTraverseVisitor(LevTraverseCallback func = nullptr);

			void SetTraverseCallback(LevTraverseCallback func);
			void Apply(const Node<LevSceneObject>& node);
			void Apply(Node<LevSceneObject>& node);

		private:
			LevTraverseCallback m_traverseCallback;
			std::vector<const Node<LevSceneObject>*> m_traverseStack;
		};
	}
}