#include "LevSceneUtil.h"
#include "LevMeshObject.h"
#include "LevSceneObject.h"
#include "LevRAttrRenderObjectAttributeBinder.h"

namespace Leviathan
{
	namespace Scene
	{
		bool LevSceneUtil::InitSceneNodeWithMeshFile(const char * mesh_file, unsigned scene_object_mask, LPtr<LevSceneNode>& out_scene_node)
		{
			LPtr<LevMeshObject> mesh_object = new LevMeshObject;
			EXIT_IF_FALSE(mesh_object->LoadMeshFile(mesh_file));

			LPtr<LevSceneObject> scene_object = new LevSceneObject(scene_object_mask);
			EXIT_IF_FALSE(scene_object->SetObjectDesc(TryCast<LevMeshObject, LevSceneObjectDescription>(mesh_object)));

			out_scene_node.Reset(new LevSceneNode(scene_object));
			return true;
		}

		// TODO: Handle different bind_type
		bool LevSceneUtil::BindMeshDataToRenderAttribute(LevSceneNode& node, int bind_type_mask)
		{
			const Scene::LevMeshObject* meshes = dynamic_cast<const Scene::LevMeshObject*>(&node.GetNodeData()->GetObjectDesc());
			EXIT_IF_FALSE(meshes);

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
				for (unsigned i = 0; i < 3 * sub_mesh_index_count; i++)
				{
					index_buffer_pointer[0] = index[i] + last_index;
					index_buffer_pointer++;
				}

				last_index += sub_mesh_vertex_count;
				vertex_buffer_pointer += 3 * sub_mesh_vertex_count;
			}

			LPtr<Scene::LevRAttrRenderObjectAttributeBinder> attribute_binder = new Scene::LevRAttrRenderObjectAttributeBinder(vertex_count);
			attribute_binder->BindAttribute(0, new LevRenderObjectAttribute(Scene::RenderObjectAttributeType::EROAT_FLOAT, 3 * sizeof(float), vertex_buffer));
			attribute_binder->SetIndexAttribute(new LevRenderObjectAttribute(Scene::RenderObjectAttributeType::EROAT_UINT, sizeof(unsigned), index_buffer));
			node.GetNodeData()->AddAttribute(TryCast<Scene::LevRAttrRenderObjectAttributeBinder, Scene::LevSceneObjectAttribute>(attribute_binder));

			return true;
		}

		bool LevSceneUtil::GenerateBallNode(const float* ball_center, float ball_radius, LPtr<LevSceneNode>& out_ball_node)
		{
			constexpr float angle_delta = 5.0f * PI_FLOAT / 180.0f;
			constexpr size_t step_count = PI_FLOAT / angle_delta;

			Eigen::Vector3f current_scan_half_ball[step_count + 1];

			// Init base scan line
			for (size_t i = 0; i <= step_count; i++)
			{
				float coord[] = { sinf(angle_delta * i) , cosf(angle_delta * i) , 0.0f };
				memcpy(current_scan_half_ball[i].data(), coord, 3 * sizeof(float));
			}

			// Generate step rotation matrix (Rotate with x axis)
			Eigen::Matrix3f rotation_step;
			float rotation[] =
			{
				1.0f,						 0.0f,			   	   0.0f,
				0.0f,			cosf(angle_delta),	  sinf(angle_delta),
				0.0f,		   -sinf(angle_delta),	  cosf(angle_delta),
			};

			memcpy(rotation_step.data(), rotation, sizeof(rotation));

			std::vector<Eigen::Vector3f> m_vertices;
			std::vector<unsigned> m_indices;
			unsigned current_index_offset = 0;

			for (auto& vertex : current_scan_half_ball)
			{
				m_vertices.push_back(vertex);
			}

			/*
				Current scan line:	0 - 1 - 2 - 3 - 4 - 5
									| / | / | / | / | / |
				Next scan line:		6 - 7 - 8 - 9 - 10 - 11
			*/

			unsigned index_delta[2 * 3 * step_count];
			for (size_t i = 0; i < step_count; i++)
			{
				unsigned* data = index_delta + 2 * 3 * i;
				data[0] = i;
				data[1] = i + 1;
				data[2] = step_count + 1 + i;
				data[3] = data[2];
				data[4] = data[1];
				data[5] = data[2] + 1;
			}

			for (size_t i = 0; i < step_count; i++)
			{
				Eigen::Vector3f next_scan_half_ball[step_count + 1];

				for (size_t j = 0; j <= step_count; j++)
				{
					next_scan_half_ball[j] = rotation_step * current_scan_half_ball[j];
					m_vertices.push_back(next_scan_half_ball[j]);
				}

				for (auto index : index_delta)
				{
					m_indices.push_back(index + current_index_offset);
				}

				memcpy(current_scan_half_ball->data(), next_scan_half_ball->data(), sizeof(next_scan_half_ball));

				current_index_offset += (step_count + 1);
			}

			// Convert vertices data
			LPtr<RAIIBufferData> vertices_buffer_data = new RAIIBufferData(m_vertices.size() * 3 * sizeof(float));
			float* coord_data = static_cast<float*>(vertices_buffer_data->GetArrayData());

			for (size_t i = 0; i < m_vertices.size(); i++)
			{
				float* data = coord_data + 3 * i;
				memcpy(data, m_vertices[i].data(), 3 * sizeof(float));
			}

			LPtr<LevRAttrRenderObjectAttributeBinder> attribute_binder = new LevRAttrRenderObjectAttributeBinder(m_vertices.size());

			LPtr<LevRenderObjectAttribute> vertices_attribute = new LevRenderObjectAttribute(EROAT_FLOAT, 3 * sizeof(float), vertices_buffer_data);
			attribute_binder->BindAttribute(0, vertices_attribute);

			LPtr<RAIIBufferData> indices_buffer_data = new RAIIBufferData(m_indices.size() * sizeof(unsigned));
			unsigned* indices_data = static_cast<unsigned*>(indices_buffer_data->GetArrayData());
			for (size_t i = 0; i < m_indices.size(); i++)
			{
				unsigned* data = indices_data + i;
				*data = m_indices[i];
			}

			//memcpy(indices_buffer_data->GetArrayData(), &m_indices[0], m_indices.size() * sizeof(unsigned));

			LPtr<LevRenderObjectAttribute> index_attribute = new LevRenderObjectAttribute(EROAT_UINT, sizeof(unsigned), indices_buffer_data);
			attribute_binder->SetIndexAttribute(index_attribute);

			LPtr<LevSceneObject> object = new LevSceneObject(ELSOT_DYNAMIC);
			object->AddAttribute(TryCast<LevRAttrRenderObjectAttributeBinder, LevSceneObjectAttribute>(attribute_binder));

			out_ball_node.Reset(new LevSceneNode(object));

			return true;
		}

		bool LevSceneUtil::GeneratePlaneNode(const float* plane_node0, const float* plane_node1, const float* plane_node2, const float* plane_node3, LPtr<LevSceneNode>& out_plane_node)
		{
			return true;
		}

	}
}