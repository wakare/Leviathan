#pragma once
#include "LevScene.h"
#include "LPtr.h"

namespace Leviathan
{
	namespace Scene
	{
		class LevNumericalUniform;
		class LevSceneNode;

		class LEV_SCENE_API LevNormalScene : public LevScene
		{
		public:
			LevNormalScene();
			virtual void Update();

			LPtr<LevSceneNode> GetLightRootNode();

		private:
			bool _init_root_node();
			bool _init_main_camera();
			bool _init_default_light_root_node();

			void _update_camera();

			LPtr<LevSceneNode> m_camera_node;
			LPtr<LevNumericalUniform> m_default_view_matrix;
			LPtr<LevNumericalUniform> m_default_proj_matrix;

			LPtr<LevSceneNode> m_light_root_node;
		};
	}
}