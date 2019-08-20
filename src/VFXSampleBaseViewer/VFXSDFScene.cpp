#include "VFXSDFScene.h"
#include "VFXSDFShaderProgram.h"
#include "SDFVoxelManager.h"
#include "LevTextureObject.h"
#include "LevSceneUtil.h"
#include "LevTextureUniform.h"
#include "LevRAttrUniformManager.h"
#include "LevSceneData.h"
#include "LevRAttrShaderProgram.h"
#include "LevRAttrRenderStateManager.h"
#include "LevRenderStatePointSize.h"

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

			float sphere_radius = 7.0f;

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
			InitCubeNode();
			//InitDebugNode();
			UpdateSDFToTexture();
		}

		void VFXSDFScene::InitRenderNode()
		{
			m_render_node.Reset(new LevSceneNode(new LevSceneObject(ELSOT_EMPTY)));
			m_sdf_texture_uniform = new Scene::LevTextureUniform("SDF_TEXTURE");

			LPtr<LevNumericalUniform> SDF_MIN = new LevNumericalUniform("SDF_MIN", TYPE_FLOAT_VEC3);
			LPtr<RAIIBufferData> min_data = new RAIIBufferData(3 * sizeof(float));
			min_data->SetArrayData(m_sdf_manager->GetMin(), 3 * sizeof(float));
			SDF_MIN->SetData(min_data);
			
			LPtr<LevNumericalUniform> SDF_GRID_LENGTH = new LevNumericalUniform("SDF_GRID_LENGTH", TYPE_FLOAT_VEC3);
			LPtr<RAIIBufferData> length_data = new RAIIBufferData(3 * sizeof(float));
			length_data->SetArrayData(m_sdf_manager->GetSize(), 3 * sizeof(float));
			SDF_GRID_LENGTH->SetData(length_data);

			LPtr<LevNumericalUniform> model_matrix_uniform = nullptr;
			LevSceneUtil::GenerateIdentityMatrixUniform("modelMatrix", model_matrix_uniform);

			LPtr<LevNumericalUniform> world_matrix_uniform = nullptr;
			LevSceneUtil::GenerateIdentityMatrixUniform("worldMatrix", world_matrix_uniform);

			LPtr<Scene::LevRAttrUniformManager> uniform_manager = new Scene::LevRAttrUniformManager;
			
			uniform_manager->AddUniform(model_matrix_uniform.To<ILevUniform>());
			uniform_manager->AddUniform(world_matrix_uniform.To<ILevUniform>());
			uniform_manager->AddUniform(m_sdf_texture_uniform.To<ILevUniform>());
			uniform_manager->AddUniform(SDF_MIN.To<ILevUniform>());
			uniform_manager->AddUniform(SDF_GRID_LENGTH.To<ILevUniform>());

			LPtr<Scene::LevShaderProgram> shader_program = new Scene::LevShaderProgram;
			shader_program->m_vert_shader = vfx_sdf_vert;
			shader_program->m_frag_shader = vfx_sdf_frag;

			LPtr<Scene::LevRAttrShaderProgram> shader_program_attr = new Scene::LevRAttrShaderProgram;
			shader_program_attr->SetShaderProgram(shader_program);

			m_render_node->GetNodeData()->AddAttribute(shader_program_attr);
			m_render_node->GetNodeData()->AddAttribute(uniform_manager);

			GetSceneData().AddSceneNodeToRoot(m_render_node);
			m_render_node->AddChild(GetSceneData().GetMainCameraNode());
			GetSceneData().GetMainCamera()->LookAt(Eigen::Vector3f( 0.0f, 0.0f, 0.0f ), 10.0f);
		}

		void VFXSDFScene::InitCubeNode()
		{
			const float cube_center[] = { 0.0f, 0.0f, 0.0f };
			const float cube_size = 10.0f;

			LPtr<LevSceneNode> cube_node;
			Scene::LevSceneUtil::GenerateCube(cube_center, cube_size, cube_node);
			LEV_ASSERT(cube_node);

			m_render_node->AddChild(cube_node);
		}

		void VFXSDFScene::InitDebugNode()
		{
			std::vector<float> vertices;

			float min[3] = { -10.0f, -10.0f, -10.0f };
			float step[3] = { 0.5f, 0.5f, 0.5f };
			unsigned step_count = 40;

			for (unsigned i = 0 ; i < step_count; i++)
			{
				for (unsigned j = 0; j < step_count; j++)
				{
					for (unsigned k = 0; k < step_count; k++)
					{
						float temp_point[] = { min[0] + i * step[0] ,min[1] + j * step[1] ,min[2] + k * step[2] };
						vertices.push_back(temp_point[0]);
						vertices.push_back(temp_point[1]);
						vertices.push_back(temp_point[2]);
					}
				}
			}

			LPtr<LevSceneNode> points_node;
			LevSceneUtil::GeneratePoints(&vertices[0], nullptr, vertices.size() / 3, points_node);

			LPtr<LevRAttrRenderStateManager> render_state_manager = new LevRAttrRenderStateManager;
			render_state_manager->UpdateRenderState(new LevRenderStatePointSize(3));

			points_node->GetNodeData()->AddAttribute(render_state_manager);

			m_render_node->AddChild(points_node);
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


