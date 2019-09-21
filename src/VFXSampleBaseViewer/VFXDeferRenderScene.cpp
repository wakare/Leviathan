#include "VFXDeferRenderScene.h"
#include "LevSceneUtil.h"
#include "LevRAttrUniformManager.h"
#include "LevSceneData.h"
#include "LevRAttrFrameBufferObject.h"
#include "LevFrameBufferObject.h"
#include "LevRAttrShaderProgram.h"
#include "BaseShaderSource.h"
#include "LevTextureObject.h"
#include "LevTextureUniform.h"
#include "LevRAttrRenderObjectAttributeBinder.h"
#include "LevRAttrDepthFunc.h"

namespace Leviathan
{
	namespace Viewer
	{
		VFXDeferRenderScene::VFXDeferRenderScene()
			: m_root_node(new LevSceneNode(new LevSceneObject(ELSOT_EMPTY)))
			, m_scene_node(new LevSceneNode(new LevSceneObject(ELSOT_EMPTY)))
			, m_quad_node(new LevSceneNode(new LevSceneObject(ELSOT_EMPTY)))
			, m_texture_color_object(nullptr)
			, m_texture_depth_object(nullptr)
		{
			GetSceneData().AddSceneNodeToRoot(m_root_node);
			m_root_node->AddChild(m_scene_node);
			m_root_node->AddChild(m_quad_node);

			const LSPtr<LevRAttrDepthFunc> depth = new LevRAttrDepthFunc(ELDFP_LESS);
			m_scene_node->GetNodeData()->AddAttribute(depth);

			_init_frame_buffer_object();
			_init_scene_node();
			_init_quad_node();
		}

		bool VFXDeferRenderScene::_init_frame_buffer_object()
		{
			const LSPtr<LevRAttrFrameBufferObject> frame_buffer_object = new LevRAttrFrameBufferObject();
			
			m_texture_color_object = new LevTextureObject(ELTT_2D_COLOR_TEXTURE, 800, 600, 1, nullptr);
			frame_buffer_object->GetFrameBufferObject()->Attach(ELFAT_COLOR_ATTACHMENT0, m_texture_color_object.To<LevAttachment>());

			m_texture_depth_object = new LevTextureObject(ELTT_2D_DEPTH_TEXTURE, 800, 600, 1, nullptr);
			frame_buffer_object->GetFrameBufferObject()->Attach(ELFAT_DEPTH_ATTACHMENT0, m_texture_depth_object.To<LevAttachment>());

			return m_scene_node->GetNodeData()->AddAttribute(frame_buffer_object);
		}

		void VFXDeferRenderScene::_init_scene_node()
		{
			/*
				Random generate sphere light
			*/
			constexpr size_t RANDOM_BALL_COUNT = 100;
			for (size_t i = 0; i < RANDOM_BALL_COUNT; i++)
			{
				LSPtr<LevSceneNode> sphere_node = nullptr;

				float rand_x = (1.0f * rand() / RAND_MAX) * 100.0f;
				float rand_y = (1.0f * rand() / RAND_MAX) * 100.0f;
				float rand_z = (1.0f * rand() / RAND_MAX) * 100.0f;
				float rand_radius = (1.0f * rand() / RAND_MAX) * 5.0f;

				float center[] = { rand_x, rand_y, rand_z };
				LevSceneUtil::GenerateBallNode(center, rand_radius, sphere_node);

				// Set uniform
				LSPtr<LevRAttrUniformManager> uniform_manager = new LevRAttrUniformManager;
				sphere_node->GetNodeData()->AddAttribute(TryCast<LevRAttrUniformManager, LevSceneObjectAttribute>(uniform_manager));

				LSPtr<LevNumericalUniform> model_matrix_uniform = nullptr;
				LevSceneUtil::GenerateIdentityMatrixUniform("modelMatrix", model_matrix_uniform);

				LSPtr<LevNumericalUniform> world_matrix_uniform = nullptr;
				LevSceneUtil::GenerateIdentityMatrixUniform("worldMatrix", world_matrix_uniform);

				uniform_manager->AddUniform(TryCast<LevNumericalUniform, ILevUniform>(model_matrix_uniform));
				uniform_manager->AddUniform(TryCast<LevNumericalUniform, ILevUniform>(world_matrix_uniform));

				m_scene_node->AddChild(sphere_node);

				if (i > 100)
				{
					continue;
				}

				// Add first 100 light object to scene
				LSPtr<LevLight> point_light = new LevLight(ELLT_POINT_LIGHT, ELSOT_DYNAMIC);
				point_light->SetAmbientColor({ 0.0f, 0.0f, 0.0f });
				point_light->SetDiffuseColor({ 0.0f, 0.0f, 0.0f });
				point_light->SetSpecularColor({ 0.8f, 0.8f, 0.8f });

				LSPtr<LevRAttrUniformManager> point_light_uniform_manager = new LevRAttrUniformManager;
				point_light->AddAttribute(TryCast<LevRAttrUniformManager, LevSceneObjectAttribute>(point_light_uniform_manager));

				char uniform_coord_name[100];
				snprintf(uniform_coord_name, sizeof(uniform_coord_name), "point_light[%d].coord", i);

				LSPtr<LevNumericalUniform> light_coord_uniform = new LevNumericalUniform(uniform_coord_name, Scene::TYPE_FLOAT_VEC3);
				LSPtr<RAIIBufferData> light_coord_data = new RAIIBufferData(3 * sizeof(float));
				memcpy(light_coord_data->GetArrayData(), center, 3 * sizeof(float));
				light_coord_uniform->SetData(light_coord_data);

				char uniform_color_name[100];
				snprintf(uniform_color_name, sizeof(uniform_color_name), "point_light[%d].diffuse_color", i);

				LSPtr<LevNumericalUniform> light_color_uniform = new LevNumericalUniform(uniform_color_name, Scene::TYPE_FLOAT_VEC3);
				LSPtr<RAIIBufferData> light_color_data = new RAIIBufferData(3 * sizeof(float));
				float light_color[] = { 0.08f, 0.03f ,0.01f };
				memcpy(light_color_data->GetArrayData(), light_color, 3 * sizeof(float));
				light_color_uniform->SetData(light_color_data);
				
				point_light_uniform_manager->AddUniform(TryCast<LevNumericalUniform, ILevUniform>(light_coord_uniform));
				point_light_uniform_manager->AddUniform(TryCast<LevNumericalUniform, ILevUniform>(light_color_uniform));
				AddLightToLightRootNode(point_light);
			}

			// Create a plane
			const float plane_nodes[] =
			{
				-1000.0f, -1000.0f, -10.0f,
				1000.0f, -1000.0f, -10.0f,
				1000.0f, 1000.0f, -10.0f,
				-1000.0f, 1000.0f, -10.0f,
			};

			LSPtr<LevSceneNode> plane_node;
			LevSceneUtil::GeneratePlaneNode(plane_nodes, plane_nodes + 3, plane_nodes + 6, plane_nodes + 9, plane_node);

			LSPtr<LevRAttrUniformManager> plane_uniform_manager = new LevRAttrUniformManager;
			plane_node->GetNodeData()->AddAttribute(TryCast<LevRAttrUniformManager, LevSceneObjectAttribute>(plane_uniform_manager));

			m_scene_node->AddChild(plane_node);
			GetSceneData().GetMainCamera()->LookAt({ 50.0f, 50.0f, 0.0f }, 10.0f);
		}

		void VFXDeferRenderScene::_init_quad_node()
		{
			LSPtr<LevShaderProgram> shader = new LevShaderProgram;
			shader->m_vert_shader = defer_quad_vert;
			shader->m_frag_shader = defer_quad_frag;

			LSPtr<LevRAttrShaderProgram> shader_program = new LevRAttrShaderProgram;
			shader_program->SetShaderProgram(shader);

			const bool added = m_quad_node->GetNodeData()->AddAttribute(shader_program);
			LEV_ASSERT(added);

			float plane_vertices[] =
			{
				-1.0f, -1.0f, 0.0f,
				-1.0f,  1.0f, 0.0f,
				 1.0f,  1.0f, 0.0f,
				 1.0f, -1.0f, 0.0f,
			};

			LSPtr<LevSceneNode> quad_node;
			LevSceneUtil::GeneratePlaneNode(plane_vertices, plane_vertices + 3, plane_vertices + 6, plane_vertices + 9, quad_node);

			LevRAttrRenderObjectAttributeBinder* attribute_binder = nullptr;
			quad_node->GetNodeData()->GetAttribute<LevRAttrRenderObjectAttributeBinder>(attribute_binder);

			LEV_ASSERT(attribute_binder);

			float tex_coord[] =
			{
				0.0f, 0.0f,
				0.0f, 1.0f,
				1.0f, 1.0f,
				1.0f, 0.0f
			};

			LSPtr<RAIIBufferData> tex_coord_buffer = new RAIIBufferData(sizeof(tex_coord));
			memcpy(tex_coord_buffer->GetArrayData(), tex_coord, sizeof(tex_coord));
			LSPtr<LevRenderObjectAttribute> tex_attribute = new LevRenderObjectAttribute(EROAT_FLOAT, 2 * sizeof(float), tex_coord_buffer);
			attribute_binder->BindAttribute(1, tex_attribute);

			LSPtr<LevTextureUniform> texture_uniform = new LevTextureUniform("Quad_texture");
			LEV_ASSERT(m_texture_color_object);
			texture_uniform->SetUniformData(m_texture_color_object);

			LSPtr<LevRAttrUniformManager> quad_uniform_manager = new LevRAttrUniformManager;
			quad_uniform_manager->AddUniform(texture_uniform.To<ILevUniform>());
			quad_node->GetNodeData()->AddAttribute(quad_uniform_manager);

			m_quad_node->AddChild(quad_node);
		}
	}
}
