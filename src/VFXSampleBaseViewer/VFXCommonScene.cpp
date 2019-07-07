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

			// Test Code
			LPtr<LevSceneNode> mesh_node = nullptr;
			auto inited = LevSceneUtil::InitSceneNodeWithMeshFile("D:\\Resource\\Model\\2b\\lufeng.FBX", ELSOT_DYNAMIC, mesh_node);
			const Scene::LevMeshObject* meshes = dynamic_cast<const Scene::LevMeshObject*>(&mesh_node->GetNodeData()->GetObjectDesc());
			LEV_ASSERT(meshes);

			// Bind attributes
			size_t primitive_vertex_count = 0;
			size_t vertex_count = 0;

			for (auto& mesh : meshes->GetMesh())
			{
				primitive_vertex_count += mesh->GetPrimitiveCount();
				vertex_count += mesh->GetVertexCount();
			}

			LPtr<RAIIBufferData> index_buffer = new RAIIBufferData(3 * sizeof(unsigned) * primitive_vertex_count);
			LPtr<RAIIBufferData> vertex_buffer = new RAIIBufferData(3 * sizeof(float) * vertex_count);
			
			unsigned last_index = 0;

			unsigned* index_buffer_pointer = static_cast<unsigned*>(index_buffer->GetArrayData());
			float* vertex_buffer_pointer = static_cast<float*>(vertex_buffer->GetArrayData());
			
			for (auto& mesh : meshes->GetMesh())
			{
				const auto sub_mesh_vertex_count = mesh->GetVertexCount();
				const auto sub_mesh_index_count = mesh->GetPrimitiveCount();

				const auto* vertex_array = mesh->GetVertex3DCoordArray();
				memcpy(vertex_buffer_pointer, vertex_array, 3 * sizeof(float) * sub_mesh_vertex_count);

				unsigned* index = mesh->GetPrimitiveIndexArray();
				for (unsigned i = 0; i < sub_mesh_index_count; i++)
				{
					index_buffer_pointer[0] = index[i] + last_index;
					index_buffer_pointer++;
				}

				last_index += sub_mesh_vertex_count;
				vertex_buffer_pointer += 3 * sub_mesh_vertex_count;
			}

			LPtr<Scene::LevRAttrRenderObjectAttributeBinder> attribute_binder = new Scene::LevRAttrRenderObjectAttributeBinder(vertex_count);
			attribute_binder->BindAttribute(0, new LevRenderObjectAttribute(Scene::RenderObjectAttributeType::EROAT_FLOAT, 3 * sizeof(float), vertex_buffer));
			attribute_binder->SetIndexAttribute(new LevRenderObjectAttribute(Scene::RenderObjectAttributeType::EROAT_UINT, 3 * sizeof(unsigned), index_buffer));
			mesh_node->GetNodeData()->AddAttribute(TryCast<Scene::LevRAttrRenderObjectAttributeBinder, Scene::LevSceneObjectAttribute>(attribute_binder));

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

				LPtr<LevRAttrUniform> view_matrix_uniform = new LevRAttrUniform("viewMatrix", TYPE_FLOAT_MAT4);
				LPtr<RAIIBufferData> view_matrix = new RAIIBufferData(sizeof(identity_matrix));
				view_matrix->SetArrayData(GetSceneData().GetMainCamera()->GetViewportMatrix().data(), sizeof(identity_matrix));
				view_matrix_uniform->SetData(view_matrix);

				LPtr<LevRAttrUniform> proj_matrix_uniform = new LevRAttrUniform("projMatrix", TYPE_FLOAT_MAT4);
				LPtr<RAIIBufferData> proj_matrix = new RAIIBufferData(sizeof(identity_matrix));
				proj_matrix->SetArrayData(GetSceneData().GetMainCamera()->GetProjectMatrix().data(), sizeof(identity_matrix));
				proj_matrix_uniform->SetData(proj_matrix);

				LevRAttrUniformManager* uniform_manager = nullptr;
				mesh_node->GetNodeData()->GetAttribute<LevRAttrUniformManager>(uniform_manager);

				uniform_manager->AddUniform(model_matrix_uniform);
				uniform_manager->AddUniform(world_matrix_uniform);
				uniform_manager->AddUniform(view_matrix_uniform);
				uniform_manager->AddUniform(proj_matrix_uniform);

				mesh_node->GetNodeData()->SetState(ELSOS_UPDATE);
			};

			LPtr<LevTimer> mesh_timer = new LevTimer(16.6f, mesh_node_timer);
			mesh_node->GetNodeData()->SetTimer(mesh_timer);
			
			if (inited)
			{
				GetSceneData().AddSceneNode(mesh_node);
				//auto mesh = mesh_node->GetNodeData()->GetObjectDesc()

				GetSceneData().GetMainCamera()->LookAt({ -1000.0f, -1000.0f, 0.0f }, 1000.0f);
			}
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

	}
}