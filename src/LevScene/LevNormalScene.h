#pragma once
#include "LevScene.h"
#include "LSPtr.h"

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

			LSPtr<LevSceneNode> GetLightRootNode();
			
		protected:
			bool _init_root_node();
			bool _init_main_camera();
			bool _init_default_light_root_node();

			void _update_camera();

			LSPtr<LevSceneNode> m_camera_node;
			LSPtr<LevNumericalUniform> m_default_view_matrix;
			LSPtr<LevNumericalUniform> m_default_proj_matrix;

			LSPtr<LevSceneNode> m_light_root_node;
		};
	}
}