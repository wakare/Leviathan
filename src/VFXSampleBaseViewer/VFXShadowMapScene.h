#pragma once

#include "VFXCommonScene.h"
#include "LevTextureObject.h"

namespace Leviathan
{
	namespace Viewer
	{
		class LEV_VFX_SAMPLE_BASE_VIEWER_API VFXShadowMapScene : public VFXCommonScene
		{
		public:
			VFXShadowMapScene();

		private:
			bool _init_preprocess();
			bool _init_scene();

			LSPtr<LevTextureObject> m_depth_texture;

			LSPtr<LevSceneNode> m_preprocess_node;
			LSPtr<LevSceneNode> m_scene_node;

			LSPtr<LevNumericalUniform> m_light_space_view_matrix;
			LSPtr<LevNumericalUniform> m_light_space_proj_matrix;
		};
	}
}
