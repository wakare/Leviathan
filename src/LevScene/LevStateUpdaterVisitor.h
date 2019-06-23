#pragma once

#include <functional>
#include "NodeVisitor.h"
#include "LevSceneAPIDefine.h"

namespace Leviathan
{
	namespace Scene
	{
		class LevSceneObject;

		class LEV_SCENE_API LevStateUpdaterVisitor : public NodeVisitor<LevSceneObject>
		{
		public:
			typedef std::function<bool(LevSceneObject&)> LevStateUpdateCallback;

			LevStateUpdaterVisitor(LevStateUpdateCallback updater = nullptr);
			void SetStateUpdateCallback(LevStateUpdateCallback updater);

			void Apply(Node<LevSceneObject>& node);
			void Apply(const Node<LevSceneObject>& node);

		private:
			LevStateUpdateCallback m_updater;
		};
	}
}