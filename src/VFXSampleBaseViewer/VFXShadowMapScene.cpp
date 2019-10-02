#include "VFXShadowMapScene.h"
#include "ShadowMapSceneProgram.h"
#include "LevSceneNode.h"
#include "LevSceneUtil.h"
#include "LevSceneData.h"
#include "LevRAttrShaderProgram.h"
#include "LevRAttrUniformManager.h"
#include "LevFrameBufferObject.h"
#include "LevRAttrFrameBufferObject.h"
#include "LevTextureUniform.h"
#include "LevRAttrDepthFunc.h"

namespace Leviathan
{
	namespace Viewer
	{
		VFXShadowMapScene::VFXShadowMapScene()
			: m_depth_texture(nullptr)
			, m_scene_node(new LevSceneNode(new LevSceneObject(ELSOT_EMPTY)))
			, m_preprocess_node(new LevSceneNode(new LevSceneObject(ELSOT_EMPTY)))
			, m_light_space_view_matrix(nullptr)
			, m_light_space_proj_matrix(nullptr)
		{
			_init_preprocess();
			_init_scene();
			
			GetSceneData().AddSceneNodeToRoot(m_scene_node);
			GetSceneData().AddSceneNodeToRoot(m_preprocess_node);
			
			LSPtr<LevShaderProgram> shader_program = new LevShaderProgram;
			shader_program->m_vert_shader = shadow_map_vert;
			shader_program->m_frag_shader = shadow_map_frag;

			LSPtr<LevRAttrShaderProgram> attr_shader = new LevRAttrShaderProgram;
			attr_shader->SetShaderProgram(shader_program);

			GetSceneData().GetSceneRootNode().GetNodeData()->UpdateAttribute(attr_shader);

			LSPtr<LevRAttrUniformManager> uniform_manager = new LevRAttrUniformManager;
			LSPtr<LevNumericalUniform> model_matrix_uniform = nullptr;
			LSPtr<LevNumericalUniform> world_matrix_uniform = nullptr;
			LevSceneUtil::GenerateIdentityMatrixUniform("modelMatrix", model_matrix_uniform);
			LevSceneUtil::GenerateIdentityMatrixUniform("worldMatrix", world_matrix_uniform);

			uniform_manager->AddUniform(model_matrix_uniform.To<ILevUniform>());
			uniform_manager->AddUniform(world_matrix_uniform.To<ILevUniform>());

			uniform_manager->AddUniform(m_light_space_view_matrix.To<ILevUniform>());
			uniform_manager->AddUniform(m_light_space_proj_matrix.To<ILevUniform>());

			LSPtr<LevTextureUniform> depth_texture_uniform = new LevTextureUniform("DEPTH_TEXTURE");
			depth_texture_uniform->SetUniformData(m_depth_texture);

			uniform_manager->AddUniform(depth_texture_uniform.To<ILevUniform>());

			m_scene_node->GetNodeData()->AddAttribute(uniform_manager);
		}

		bool VFXShadowMapScene::_init_preprocess()
		{
			m_depth_texture = new LevTextureObject(ELTT_2D_DEPTH_TEXTURE, 800, 600, 1, nullptr);
			LSPtr<LevFrameBufferObject> fbo = new LevFrameBufferObject;
			fbo->Attach(ELFAT_DEPTH_ATTACHMENT0, m_depth_texture.To<LevAttachment>());

			LSPtr<LevRAttrFrameBufferObject> attr_fbo = new LevRAttrFrameBufferObject;
			attr_fbo->SetFrameBufferObject(fbo);

			m_preprocess_node->GetNodeData()->AddAttribute(attr_fbo);

			LSPtr<LevShaderProgram> preprocess = new LevShaderProgram;
			preprocess->m_vert_shader = shadow_preprocess_vert;
			preprocess->m_frag_shader = shadow_preprocess_frag;

			LSPtr<LevRAttrShaderProgram> preprocess_shader = new LevRAttrShaderProgram;
			preprocess_shader->SetShaderProgram(preprocess);

			m_preprocess_node->GetNodeData()->AddAttribute(preprocess_shader);

			LSPtr<LevRAttrUniformManager> uniform_manager = new LevRAttrUniformManager;
			LSPtr<LevNumericalUniform> model_matrix_uniform = nullptr;
			LSPtr<LevNumericalUniform> world_matrix_uniform = nullptr;

			LevSceneUtil::GenerateIdentityMatrixUniform("modelMatrix", model_matrix_uniform);
			LevSceneUtil::GenerateIdentityMatrixUniform("worldMatrix", world_matrix_uniform);

			uniform_manager->AddUniform(model_matrix_uniform.To<ILevUniform>());
			uniform_manager->AddUniform(world_matrix_uniform.To<ILevUniform>());

			m_preprocess_node->GetNodeData()->AddAttribute(uniform_manager);

			float view_matrix_data[] =
			{
				0.0f, 0.0f, 50.0f,
				0.0f, 0.0f, 10.0f,
				0.0f, 1.0f, 0.0f
			};

			LevSceneUtil::GenerateLookAtMatrixUniform("light_viewMatrix", view_matrix_data, view_matrix_data + 3, view_matrix_data + 6, m_light_space_view_matrix);

			LevSceneUtil::GenerateProjectionMatrix("light_projMatrix", ANGLE_TO_RADIAN(60.0f), 800.0f / 600.0f, 0.1f, 1000.0f, m_light_space_proj_matrix);

			uniform_manager->AddUniform(m_light_space_view_matrix.To<ILevUniform>());
			uniform_manager->AddUniform(m_light_space_proj_matrix.To<ILevUniform>());

			LSPtr<LevRAttrDepthFunc> depth_func = new LevRAttrDepthFunc(ELDFP_LESS);
			m_preprocess_node->GetNodeData()->AddAttribute(depth_func);

			return true;
		}

		bool VFXShadowMapScene::_init_scene()
		{
			LSPtr<LevSceneNode> plane_node = nullptr;
			float plane_vertices[] =
			{
				-100.0f, -100.0f, 0.0f,
				 100.0f, -100.0f, 0.0f,
				 100.0f, 100.0f, 0.0f,
				-100.0f, 100.0f, 0.0f,
			};

			LevSceneUtil::GeneratePlaneNode(plane_vertices, plane_vertices + 3, plane_vertices + 6, plane_vertices + 9, plane_node);

			LSPtr<LevSceneNode> sphere_node = nullptr;
			float sphere_center[] = { 0.0f, 0.0f, 10.0f };

			LevSceneUtil::GenerateBallNode(sphere_center, 5.0f, sphere_node);

			m_scene_node->AddChild(plane_node);
			m_scene_node->AddChild(sphere_node);

			m_preprocess_node->AddChild(plane_node);
			m_preprocess_node->AddChild(sphere_node);

			float camera_data[] =
			{
				0.0f, 0.0f, 50.0f,
				0.0f, 0.0f, 10.0f,
				0.0f, 1.0f, 0.0f
			};

			GetSceneData().GetMainCamera()->Set(camera_data, camera_data + 3, camera_data + 6);

			return true;
		}
	}
}
