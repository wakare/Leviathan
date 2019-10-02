#pragma once

#include "VFXCommonScene.h"
#include "LevTextureUniform.h"

class PictureObject;

namespace Leviathan
{
	namespace Viewer
	{
		class LEV_VFX_SAMPLE_BASE_VIEWER_API VFXSkyBoxScene : public VFXCommonScene
		{
		public:
			VFXSkyBoxScene();

		private:
			bool _load_skybox_texture(const char* skybox_texture_folder_path);
			bool _init_scene();

			LSPtr<LevTextureUniform> m_skybox_uniform;
			LSPtr<RAIIBufferData> m_texture_data;
			LSPtr<LevSceneNode> m_root_node;

			std::vector<LSPtr<PictureObject>> pictures;
		};
	}
}
