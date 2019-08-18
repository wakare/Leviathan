#include "VFXDeferRenderScene.h"
#include "LevSceneUtil.h"
#include "LevRAttrUniformManager.h"
#include "LevSceneData.h"

namespace Leviathan
{
	namespace Viewer
	{
		VFXDeferRenderScene::VFXDeferRenderScene()
			: VFXCommonScene()
		{
			_createDeferRenderTestScene();
		}

		void VFXDeferRenderScene::_createDeferRenderTestScene()
		{
			/*
				Random generate sphere light
			*/
			constexpr size_t RANDOM_BALL_COUNT = 100;
			for (size_t i = 0; i < RANDOM_BALL_COUNT; i++)
			{
				LPtr<LevSceneNode> sphere_node = nullptr;

				float rand_x = (1.0f * rand() / RAND_MAX) * 100.0f;
				float rand_y = (1.0f * rand() / RAND_MAX) * 100.0f;
				float rand_z = (1.0f * rand() / RAND_MAX) * 100.0f;
				float rand_radius = (1.0f * rand() / RAND_MAX) * 5.0f;

				float center[] = { rand_x, rand_y, rand_z };
				LevSceneUtil::GenerateBallNode(center, rand_radius, sphere_node);

				// Set uniform
				LPtr<LevRAttrUniformManager> uniform_manager = new LevRAttrUniformManager;
				sphere_node->GetNodeData()->AddAttribute(TryCast<LevRAttrUniformManager, LevSceneObjectAttribute>(uniform_manager));

				LPtr<LevRAttrNumericalUniform> model_matrix_uniform = nullptr;
				LevSceneUtil::GenerateIdentityMatrixUniform("modelMatrix", model_matrix_uniform);

				LPtr<LevRAttrNumericalUniform> world_matrix_uniform = nullptr;
				LevSceneUtil::GenerateIdentityMatrixUniform("worldMatrix", world_matrix_uniform);

				uniform_manager->AddUniform(TryCast<LevRAttrNumericalUniform, ILevRAttrUniform>(model_matrix_uniform));
				uniform_manager->AddUniform(TryCast<LevRAttrNumericalUniform, ILevRAttrUniform>(world_matrix_uniform));

				GetSceneData().AddSceneNodeToRoot(sphere_node);

				if (i > 100)
				{
					continue;
				}

				// Add first 100 light object to scene
				LPtr<LevLight> point_light = new LevLight(ELLT_POINT_LIGHT, ELSOT_DYNAMIC);
				point_light->SetAmbientColor({ 0.0f, 0.0f, 0.0f });
				point_light->SetDiffuseColor({ 0.0f, 0.0f, 0.0f });
				point_light->SetSpecularColor({ 0.8f, 0.8f, 0.8f });

				LPtr<LevRAttrUniformManager> point_light_uniform_manager = new LevRAttrUniformManager;
				point_light->AddAttribute(TryCast<LevRAttrUniformManager, LevSceneObjectAttribute>(point_light_uniform_manager));

				char uniform_coord_name[100];
				snprintf(uniform_coord_name, sizeof(uniform_coord_name), "point_light[%d].coord", i);

				LPtr<LevRAttrNumericalUniform> light_coord_uniform = new LevRAttrNumericalUniform(uniform_coord_name, Scene::TYPE_FLOAT_VEC3);
				LPtr<RAIIBufferData> light_coord_data = new RAIIBufferData(3 * sizeof(float));
				memcpy(light_coord_data->GetArrayData(), center, 3 * sizeof(float));
				light_coord_uniform->SetData(light_coord_data);

				char uniform_color_name[100];
				snprintf(uniform_color_name, sizeof(uniform_color_name), "point_light[%d].diffuse_color", i);

				LPtr<LevRAttrNumericalUniform> light_color_uniform = new LevRAttrNumericalUniform(uniform_color_name, Scene::TYPE_FLOAT_VEC3);
				LPtr<RAIIBufferData> light_color_data = new RAIIBufferData(3 * sizeof(float));
				float light_color[] = { 0.08f, 0.03f ,0.01f };
				memcpy(light_color_data->GetArrayData(), light_color, 3 * sizeof(float));
				light_color_uniform->SetData(light_color_data);
				
				point_light_uniform_manager->AddUniform(TryCast<LevRAttrNumericalUniform, ILevRAttrUniform>(light_coord_uniform));
				point_light_uniform_manager->AddUniform(TryCast<LevRAttrNumericalUniform, ILevRAttrUniform>(light_color_uniform));
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

			LPtr<LevSceneNode> plane_node = nullptr;
			LevSceneUtil::GeneratePlaneNode(plane_nodes, plane_nodes + 3, plane_nodes + 6, plane_nodes + 9, plane_node);

			LPtr<LevRAttrUniformManager> plane_uniform_manager = new LevRAttrUniformManager;
			plane_node->GetNodeData()->AddAttribute(TryCast<LevRAttrUniformManager, LevSceneObjectAttribute>(plane_uniform_manager));

			plane_node->GetNodeData()->AddAttribute(TryCast<LevRAttrUniformManager, LevSceneObjectAttribute>(plane_uniform_manager));

			GetSceneData().AddSceneNodeToRoot(plane_node);
			GetSceneData().GetMainCamera()->LookAt({ 50.0f, 50.0f, 0.0f }, 10.0f);
		}

	}
}
