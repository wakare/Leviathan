#include "VFXCommonScene.h"
#include "LevSceneData.h"
#include "LevSceneNode.h"
#include "LevSceneUtil.h"
#include "LevSceneObject.h"
#include "LevSceneObjectDescription.h"
#include "LevNormalScene.h"
#include "LevRAttrRenderObjectAttributeBinder.h"
#include "LevMeshObject.h"
#include "LevRAttrUniform.h"
#include "LevTimer.h"
#include "LevRAttrUniformManager.h"

namespace Leviathan
{
	namespace Viewer
	{
		VFXCommonScene::VFXCommonScene()
			: LevNormalScene()
		{
			Init(LevSceneType::ELST_3D_SCENE);

			_createSphereTestScene();
			//_createMeshTestScene();
		}

		bool VFXCommonScene::AddLight(LPtr<Scene::LevLight> light)
		{
			LPtr<Scene::LevSceneNode> m_light_node = new Scene::LevSceneNode(TryCast<Scene::LevLight, Scene::LevSceneObject>(light));
			return GetSceneData().AddSceneNode(m_light_node);
		}

		bool VFXCommonScene::SetCamera(LPtr<Scene::LevCamera> camera)
		{
			return GetSceneData().SetMainCamera(camera);
		}

		void VFXCommonScene::_createMeshTestScene()
		{
			// Test Code
			LPtr<LevSceneNode> mesh_node = nullptr;
			auto inited = LevSceneUtil::InitSceneNodeWithMeshFile("D:\\Resource\\Model\\2b\\lufeng.FBX", ELSOT_DYNAMIC, mesh_node);
			LEV_ASSERT(inited);

			bool binded = LevSceneUtil::BindMeshDataToRenderAttribute(*mesh_node, Scene::LevSceneUtil::EMBDT_INDEX | Scene::LevSceneUtil::EMBDT_COORD);
			LEV_ASSERT(binded);

			LPtr<LevRAttrUniformManager> uniform_manager = new LevRAttrUniformManager;
			mesh_node->GetNodeData()->AddAttribute(TryCast<LevRAttrUniformManager, LevSceneObjectAttribute>(uniform_manager));

			// Set updator
			auto mesh_node_timer = [mesh_node, this](const LevTimer&)
			{
				// Add default uniform
				float identity_matrix[] =
				{
					1.0f, 0.0f, 0.0f, 0.0f,
					0.0f, 1.0f, 0.0f, 0.0f,
					0.0f, 0.0f, 1.0f, 0.0f,
					0.0f, 0.0f, 0.0f, 1.0f
				};

				LPtr<LevRAttrUniform> model_matrix_uniform = new LevRAttrUniform("modelMatrix", TYPE_FLOAT_MAT4);
				LPtr<RAIIBufferData> model_matrix = new RAIIBufferData(sizeof(identity_matrix));
				model_matrix->SetArrayData(identity_matrix, sizeof(identity_matrix));
				model_matrix_uniform->SetData(model_matrix);

				LPtr<LevRAttrUniform> world_matrix_uniform = new LevRAttrUniform("worldMatrix", TYPE_FLOAT_MAT4);
				LPtr<RAIIBufferData> world_matrix = new RAIIBufferData(sizeof(identity_matrix));
				world_matrix->SetArrayData(identity_matrix, sizeof(identity_matrix));
				world_matrix_uniform->SetData(world_matrix);

				LevRAttrUniformManager* uniform_manager = nullptr;
				mesh_node->GetNodeData()->GetAttribute<LevRAttrUniformManager>(uniform_manager);

				uniform_manager->AddUniform(model_matrix_uniform);
				uniform_manager->AddUniform(world_matrix_uniform);

				mesh_node->GetNodeData()->SetState(ELSOS_UPDATE);
			};

			LPtr<LevTimer> mesh_timer = new LevTimer(16.6f, mesh_node_timer);
			mesh_node->GetNodeData()->SetTimer(mesh_timer);

			GetSceneData().AddSceneNode(mesh_node);
			GetSceneData().GetMainCamera()->LookAt({ -1000.0f, -1000.0f, 0.0f }, 1000.0f);
		}

		void VFXCommonScene::_createSphereTestScene()
		{
			LPtr<LevSceneNode> sphere_node = nullptr;
			float center[] = { 10.0f, 10.0f, 10.0f };
			auto generated = LevSceneUtil::GenerateBallNode(center, 10.0f, sphere_node);
			LEV_ASSERT(generated);

			// Set uniform
			// Add default uniform
			float identity_matrix[] =
			{
				1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f
			};

			LPtr<LevRAttrUniformManager> uniform_manager = new LevRAttrUniformManager;
			sphere_node->GetNodeData()->AddAttribute(TryCast<LevRAttrUniformManager, LevSceneObjectAttribute>(uniform_manager));

			LPtr<LevRAttrUniform> model_matrix_uniform = new LevRAttrUniform("modelMatrix", TYPE_FLOAT_MAT4);
			LPtr<RAIIBufferData> model_matrix = new RAIIBufferData(sizeof(identity_matrix));
			model_matrix->SetArrayData(identity_matrix, sizeof(identity_matrix));
			model_matrix_uniform->SetData(model_matrix);

			LPtr<LevRAttrUniform> world_matrix_uniform = new LevRAttrUniform("worldMatrix", TYPE_FLOAT_MAT4);
			LPtr<RAIIBufferData> world_matrix = new RAIIBufferData(sizeof(identity_matrix));
			world_matrix->SetArrayData(identity_matrix, sizeof(identity_matrix));
			world_matrix_uniform->SetData(world_matrix);

			uniform_manager->AddUniform(model_matrix_uniform);
			uniform_manager->AddUniform(world_matrix_uniform);

			GetSceneData().AddSceneNode(sphere_node);
			
			// Create a plane
			const float plane_nodes[] = 
			{
				-10.0f, -10.0f, -10.0f,
				-10.0f, 10.0f, -10.0f,
				10.0f, -10.0f, -10.0f,
				10.0f, 10.0f, -10.0f,
			};

			LPtr<LevSceneNode> plane_node = nullptr;
			LevSceneUtil::GeneratePlaneNode(plane_nodes, plane_nodes + 3, plane_nodes + 6, plane_nodes + 9, plane_node);
			
			LPtr<LevRAttrUniformManager> plane_uniform_manager = new LevRAttrUniformManager;
			sphere_node->GetNodeData()->AddAttribute(TryCast<LevRAttrUniformManager, LevSceneObjectAttribute>(plane_uniform_manager));

			LPtr<LevRAttrUniform> plane_model_matrix_uniform = nullptr;
			LevSceneUtil::GenerateIdentityMatrixUniform("modelMatrix", plane_model_matrix_uniform);

			LPtr<LevRAttrUniform> plane_world_matrix_uniform = nullptr;
			LevSceneUtil::GenerateIdentityMatrixUniform("worldMatrix", plane_world_matrix_uniform);

			plane_uniform_manager->AddUniform(plane_model_matrix_uniform);
			plane_uniform_manager->AddUniform(plane_world_matrix_uniform);

			plane_node->GetNodeData()->AddAttribute(TryCast<LevRAttrUniformManager, LevSceneObjectAttribute>(plane_uniform_manager));

			GetSceneData().AddSceneNode(plane_node);
			GetSceneData().GetMainCamera()->LookAt({ 0.0f, 0.0f, 0.0f }, 10.0f);
		}

	}
}