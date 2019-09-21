#pragma once

#include "VFXCommonScene.h"
#include "LevTextureObject.h"

namespace Leviathan
{
	namespace Viewer
	{
		class LEV_VFX_SAMPLE_BASE_VIEWER_API VFXDeferRenderScene : public VFXCommonScene
		{
		public:
			VFXDeferRenderScene();

		private:
			bool _init_frame_buffer_object();
			void _init_scene_node();
			void _init_quad_node();

			LSPtr<LevSceneNode> m_root_node;
			LSPtr<LevSceneNode> m_scene_node;
			LSPtr<LevSceneNode> m_quad_node;
			LSPtr<LevTextureObject> m_texture_color_object;
			LSPtr<LevTextureObject> m_texture_normal_object;
			LSPtr<LevTextureObject> m_texture_depth_object;
		};
	}
}
