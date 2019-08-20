#pragma once

#include "VFXCommonScene.h"
#include <memory>

namespace Leviathan
{
	namespace Scene
	{
		class LevTextureObject;
		class LevTextureUniform;
	}

	namespace Viewer
	{
		class SDFVoxelManager;

		class LEV_VFX_SAMPLE_BASE_VIEWER_API VFXSDFScene : public VFXCommonScene
		{
		public:
			VFXSDFScene();

		private:
			void InitRenderNode();
			void InitCubeNode();
			void InitDebugNode();
			void UpdateSDFToTexture();

			float m_sdf_range[6];

			LPtr<Scene::LevSceneNode> m_render_node;
			LPtr<Scene::LevTextureObject> m_sdf_texture;
			LPtr<Scene::LevTextureObject> m_sdf_normal_texture;
			LPtr<Scene::LevTextureUniform> m_sdf_texture_uniform;
			std::shared_ptr<SDFVoxelManager> m_sdf_manager;
		};
	}
}


