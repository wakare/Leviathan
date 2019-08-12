#include "VFXSDFScene.h"
#include "SDFVoxelManager.h"
#include "LevTextureObject.h"
#include "LevSceneUtil.h"
#include "LevRAttrTextureUniform.h"
#include "LevRAttrUniformManager.h"
#include "LevSceneData.h"

namespace Leviathan
{
	namespace Viewer
	{
		VFXSDFScene::VFXSDFScene()
			: m_sdf_manager(nullptr)
			, m_sdf_texture(nullptr)
			, m_sdf_texture_uniform(nullptr)
			, m_sdf_normal_texture(nullptr)
			, m_render_node(nullptr)
		{
			m_sdf_range[0] = -10.0f;
			m_sdf_range[1] = -10.0f;
			m_sdf_range[2] = -10.0f;

			m_sdf_range[3] = 10.0f;
			m_sdf_range[4] = 10.0f;
			m_sdf_range[5] = 10.0f;

			m_sdf_manager.reset(new SDFVoxelManager(100, m_sdf_range, m_sdf_range + 3));

			float sphere_center[3] =
			{
				0.0f, 0.0f, 0.0f
			};

			float sphere_radius = 10.0f;

			const auto sphere_sdf = [&](const float* world_coord, SDFVoxel& grid)
			{
				const float vector[3] =
				{
					sphere_center[0] - world_coord[0],
					sphere_center[1] - world_coord[1],
					sphere_center[2] - world_coord[2],
				};

				const float radius = sqrtf(vector[0] * vector[0] + vector[1] * vector[1] + vector[2] * vector[2]);
				grid.weight = radius - sphere_radius;
			};

			m_sdf_manager->UpdateSDFVoxelByFunc(sphere_sdf);

			InitRenderNode();
			UpdateSDFToTexture();
		}

		void VFXSDFScene::InitRenderNode()
		{
			const float cube_center[] = { 0.0f, 0.0f, 0.0f };
			const float cube_size = 5.0f;

			Scene::LevSceneUtil::GenerateCube(cube_center, cube_size, m_render_node);
			LEV_ASSERT(m_render_node);

			m_sdf_texture_uniform = new Scene::LevRAttrTextureUniform("SDF_TEXTURE");
			
			LPtr<Scene::LevRAttrUniformManager> uniform_manager = new Scene::LevRAttrUniformManager;
			uniform_manager->AddUniform(TryCast<LevRAttrTextureUniform, ILevRAttrUniform>(m_sdf_texture_uniform));

			m_render_node->GetNodeData()->AddAttribute(TryCast<Scene::LevRAttrUniformManager, Scene::LevSceneObjectAttribute>(uniform_manager));
			GetSceneData().AddSceneNodeToRoot(m_render_node);
		}

		void VFXSDFScene::UpdateSDFToTexture()
		{
			/*
			 * Fill texture data
			 */

			if (!m_sdf_texture_uniform)
			{
				return;
			}

			const auto& grids = m_sdf_manager->GetAllGrids();

			LPtr<RAIIBufferData> texture_data = new RAIIBufferData(sizeof(float) * grids.size());
			float* data = static_cast<float*>(texture_data->GetArrayData());

			for (size_t i = 0; i < grids.size(); i++)
			{
				data[i] = grids[i].weight;
			}

			m_sdf_texture = new Scene::LevTextureObject(Scene::ELTT_3D_TEXTURE, 100, 100, 100, texture_data);
			m_sdf_texture_uniform->SetUniformData(m_sdf_texture);

			m_render_node->GetNodeData()->SetState(Scene::LevSceneObjectState::ELSOS_UPDATE);
		}
	}
}


