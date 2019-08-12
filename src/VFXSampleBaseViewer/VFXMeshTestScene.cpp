#include "VFXMeshTestScene.h"
#include "LevSceneData.h"
#include "LevSceneUtil.h"
#include "LevRAttrUniformManager.h"
#include "LevTimer.h"

namespace Leviathan
{
	namespace Viewer
	{
		VFXMeshTestScene::VFXMeshTestScene()
			: VFXCommonScene()
		{
			_createMeshTestScene();
		}

		void VFXMeshTestScene::_createMeshTestScene()
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

				LPtr<LevRAttrNumericalUniform> model_matrix_uniform = new LevRAttrNumericalUniform("modelMatrix", TYPE_FLOAT_MAT4);
				LPtr<RAIIBufferData> model_matrix = new RAIIBufferData(sizeof(identity_matrix));
				model_matrix->SetArrayData(identity_matrix, sizeof(identity_matrix));
				model_matrix_uniform->SetData(model_matrix);

				LPtr<LevRAttrNumericalUniform> world_matrix_uniform = new LevRAttrNumericalUniform("worldMatrix", TYPE_FLOAT_MAT4);
				LPtr<RAIIBufferData> world_matrix = new RAIIBufferData(sizeof(identity_matrix));
				world_matrix->SetArrayData(identity_matrix, sizeof(identity_matrix));
				world_matrix_uniform->SetData(world_matrix);

				LevRAttrUniformManager* uniform_manager = nullptr;
				mesh_node->GetNodeData()->GetAttribute<LevRAttrUniformManager>(uniform_manager);

				uniform_manager->AddUniform(TryCast<LevRAttrNumericalUniform, ILevRAttrUniform>(model_matrix_uniform));
				uniform_manager->AddUniform(TryCast<LevRAttrNumericalUniform, ILevRAttrUniform>(world_matrix_uniform));

				mesh_node->GetNodeData()->SetState(ELSOS_UPDATE);
			};

			LPtr<LevTimer> mesh_timer = new LevTimer(16.6f, mesh_node_timer);
			mesh_node->GetNodeData()->SetTimer(mesh_timer);

			GetSceneData().AddSceneNodeToRoot(mesh_node);
			GetSceneData().GetMainCamera()->LookAt({ -1000.0f, -1000.0f, 0.0f }, 1000.0f);
		}

	}
}