#pragma once
#include "LevScene.h"
#include "LPtr.h"

namespace Leviathan
{
	namespace Scene
	{
		class LevRAttrUniform;
		class LevSceneNode;

		class LEV_SCENE_API LevNormalScene : public LevScene
		{
		public:
			LevNormalScene();
			virtual void Update();

		private:
			bool _init_root_node();
			bool _init_main_camera();
			bool _init_default_light();

			void _update_camera();

			LPtr<LevRAttrUniform> m_default_model_matrix;
			LPtr<LevRAttrUniform> m_default_world_matrix;
			LPtr<LevRAttrUniform> m_default_view_matrix;
			LPtr<LevRAttrUniform> m_default_proj_matrix;

			LPtr<LevSceneNode> m_camera_node;
		};
	}
}