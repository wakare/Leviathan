#include "LevSceneUtil.h"
#include "LevMeshObject.h"
#include "LevSceneObject.h"
#include "LevRAttrRenderObjectAttributeBinder.h"

namespace Leviathan
{
	namespace Scene
	{
		bool LevSceneUtil::InitSceneNodeWithMeshFile(const char * mesh_file, unsigned scene_object_mask, LSPtr<LevSceneNode>& out_scene_node)
		{
			LSPtr<LevMeshObject> mesh_object = new LevMeshObject;
			EXIT_IF_FALSE(mesh_object->LoadMeshFile(mesh_file));

			LSPtr<LevSceneObject> scene_object = new LevSceneObject(scene_object_mask);
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

			LSPtr<RAIIBufferData> index_buffer = new RAIIBufferData(3 * sizeof(unsigned) * primitive_vertex_count);
			LSPtr<RAIIBufferData> vertex_buffer = new RAIIBufferData(3 * sizeof(float) * vertex_count);

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

			LSPtr<Scene::LevRAttrRenderObjectAttributeBinder> attribute_binder = new Scene::LevRAttrRenderObjectAttributeBinder(vertex_count);
			attribute_binder->BindAttribute(0, new LevRenderObjectAttribute(Scene::RenderObjectAttributeType::EROAT_FLOAT, 3 * sizeof(float), vertex_buffer));
			attribute_binder->SetIndexAttribute(new LevRenderObjectAttribute(Scene::RenderObjectAttributeType::EROAT_UINT, sizeof(unsigned), index_buffer));
			node.GetNodeData()->AddAttribute(TryCast<Scene::LevRAttrRenderObjectAttributeBinder, Scene::LevSceneObjectAttribute>(attribute_binder));

			return true;
		}

		bool LevSceneUtil::GenerateCube(const float* cube_center, float cube_length, LSPtr<LevSceneNode>& out_cube_node)
		{
			LSPtr<RAIIBufferData> vertices_buffer = new RAIIBufferData(8 * 3 * sizeof(float));
			float* data = static_cast<float*>(vertices_buffer->GetArrayData());

			float _cube[] =
			{
				-cube_length, -cube_length, -cube_length,
				-cube_length, -cube_length, cube_length,
				-cube_length, cube_length, -cube_length,
				-cube_length, cube_length, cube_length,
				cube_length, -cube_length, -cube_length,
				cube_length, -cube_length, cube_length,
				cube_length, cube_length, -cube_length,
				cube_length, cube_length, cube_length
			};

			for (unsigned i = 0; i < 8; i++)
			{
				_cube[3 * i] += cube_center[0];
				_cube[3 * i + 1] += cube_center[1];
				_cube[3 * i + 2] += cube_center[2];
			}

			memcpy(data, _cube, sizeof(_cube));

			LSPtr<RAIIBufferData> indices_buffer = new RAIIBufferData(6 * 2 * 3 * sizeof(unsigned));
			unsigned* indices_data = static_cast<unsigned*>(indices_buffer->GetArrayData());

			unsigned indices[] =
			{
				0, 3, 1,
				0, 2, 3,
				0, 2, 6,
				0, 6, 4,
				0, 1, 5,
				0, 5, 4,
				7, 6, 4,
				7, 4, 5,
				7, 5, 1,
				7, 1, 3,
				7, 6, 2,
				7, 2, 3
			};

			memcpy(indices_data, indices, sizeof(indices));

			LSPtr<LevRAttrRenderObjectAttributeBinder> attribute_binder = new LevRAttrRenderObjectAttributeBinder(8);

			LSPtr<LevRenderObjectAttribute> vertices_attribute = new LevRenderObjectAttribute(EROAT_FLOAT, 3 * sizeof(float), vertices_buffer);
			attribute_binder->BindAttribute(0, vertices_attribute);

			LSPtr<LevRenderObjectAttribute> index_attribute = new LevRenderObjectAttribute(EROAT_UINT, sizeof(unsigned), indices_buffer);
			attribute_binder->SetIndexAttribute(index_attribute);

			LSPtr<LevSceneObject> object = new LevSceneObject(ELSOT_DYNAMIC);
			object->AddAttribute(TryCast<LevRAttrRenderObjectAttributeBinder, LevSceneObjectAttribute>(attribute_binder));

			out_cube_node.Reset(new LevSceneNode(object));

			return true;
		}

		bool LevSceneUtil::GenerateBallNode(const float* ball_center, float ball_radius, LSPtr<LevSceneNode>& out_ball_node)
		{
			constexpr float angle_delta = 15.0f * PI_FLOAT / 180.0f;
			constexpr size_t step_count = 2 * PI_FLOAT / angle_delta;

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
			std::vector<Eigen::Vector3f> m_normals;
			std::vector<unsigned> m_indices;
			unsigned current_index_offset = 0;

			for (auto& vertex : current_scan_half_ball)
			{
				m_vertices.push_back(vertex);
			}

			/*
				Current scan line:	0 - 1 - 2 - 3 - 4 - 5
									| / | / | / | / | / |
				Next scan line:		6 - 7 - 8 - 9 - 10- 11
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

			// calculate normals
			size_t vertices_count = m_vertices.size();
			for (size_t i = 0; i < vertices_count; i++)
			{
				m_normals.push_back(m_vertices[i].normalized());
			}

			// Do radius scale
			Eigen::Vector3f ball_center_vector; memcpy(ball_center_vector.data(), ball_center, 3 * sizeof(float));
			for (size_t i = 0; i < m_vertices.size(); i++)
			{
				auto& vertex = m_vertices[i];

				vertex *= ball_radius;
				vertex += ball_center_vector;
			}

			// Convert vertices data
			LSPtr<RAIIBufferData> vertices_buffer_data = new RAIIBufferData(m_vertices.size() * 3 * sizeof(float));
			float* coord_data = static_cast<float*>(vertices_buffer_data->GetArrayData());

			for (size_t i = 0; i < m_vertices.size(); i++)
			{
				float* data = coord_data + 3 * i;
				memcpy(data, m_vertices[i].data(), 3 * sizeof(float));
			}

			LSPtr<RAIIBufferData> normals_buffer_data = new RAIIBufferData(m_normals.size() * 3 * sizeof(float));
			float* normal_data = static_cast<float*>(normals_buffer_data->GetArrayData());
			for (size_t i = 0; i < m_normals.size(); i++)
			{
				float* data = normal_data + 3 * i;
				memcpy(data, m_normals[i].data(), 3 * sizeof(float));
			}

			LSPtr<LevRAttrRenderObjectAttributeBinder> attribute_binder = new LevRAttrRenderObjectAttributeBinder(m_vertices.size());

			LSPtr<LevRenderObjectAttribute> vertices_attribute = new LevRenderObjectAttribute(EROAT_FLOAT, 3 * sizeof(float), vertices_buffer_data);
			attribute_binder->BindAttribute(0, vertices_attribute);

			LSPtr<LevRenderObjectAttribute> normals_attribute = new LevRenderObjectAttribute(EROAT_FLOAT, 3 * sizeof(float), normals_buffer_data);
			attribute_binder->BindAttribute(1, normals_attribute);

			LSPtr<RAIIBufferData> indices_buffer_data = new RAIIBufferData(m_indices.size() * sizeof(unsigned));
			unsigned* indices_data = static_cast<unsigned*>(indices_buffer_data->GetArrayData());
			for (size_t i = 0; i < m_indices.size(); i++)
			{
				unsigned* data = indices_data + i;
				*data = m_indices[i];
			}

			LSPtr<LevRenderObjectAttribute> index_attribute = new LevRenderObjectAttribute(EROAT_UINT, sizeof(unsigned), indices_buffer_data);
			attribute_binder->SetIndexAttribute(index_attribute);

			LSPtr<LevSceneObject> object = new LevSceneObject(ELSOT_DYNAMIC);
			object->AddAttribute(TryCast<LevRAttrRenderObjectAttributeBinder, LevSceneObjectAttribute>(attribute_binder));

			out_ball_node.Reset(new LevSceneNode(object));

			return true;
		}

		bool LevSceneUtil::GeneratePlaneNode(const float* plane_node0, const float* plane_node1, const float* plane_node2, const float* plane_node3, LSPtr<LevSceneNode>& out_plane_node)
		{
			float vertices[12];
			memcpy(vertices, plane_node0, 3 * sizeof(float));
			memcpy(vertices + 3, plane_node1, 3 * sizeof(float));
			memcpy(vertices + 6, plane_node2, 3 * sizeof(float));
			memcpy(vertices + 9, plane_node3, 3 * sizeof(float));

			LSPtr<RAIIBufferData> vertices_buffer_data = new RAIIBufferData(sizeof(vertices));
			memcpy(vertices_buffer_data->GetArrayData(), vertices, sizeof(vertices));

			/*
				Calculate plane normal
			*/
			Eigen::Vector3f edge0;
			edge0.x() = plane_node0[0] - plane_node1[0];
			edge0.y() = plane_node0[1] - plane_node1[1];
			edge0.z() = plane_node0[2] - plane_node1[2];

			Eigen::Vector3f edge1;
			edge1.x() = plane_node1[0] - plane_node2[0];
			edge1.y() = plane_node1[1] - plane_node2[1];
			edge1.z() = plane_node1[2] - plane_node2[2];

			Eigen::Vector3f normal;
			normal = edge0.cross(edge1);
			normal.normalize();

			LSPtr<RAIIBufferData> normals_buffer_data = new RAIIBufferData(sizeof(vertices));
			float* normal_data = static_cast<float*>(normals_buffer_data->GetArrayData());
			for (size_t i = 0; i < 4; i++)
			{
				memcpy(normal_data + 3 * i, normal.data(), 3 * sizeof(float));
			}

			LSPtr<LevRenderObjectAttribute> vertex_attibute = new LevRenderObjectAttribute(EROAT_FLOAT, 3 * sizeof(float), vertices_buffer_data);
			LSPtr<LevRenderObjectAttribute> normal_attribute = new LevRenderObjectAttribute(EROAT_FLOAT, 3 * sizeof(float), normals_buffer_data);

			unsigned indexs[6] =
			{
				0, 1, 2,
				0, 2, 3
			};

			LSPtr<RAIIBufferData> index_buffer_data = new RAIIBufferData(sizeof(indexs));
			memcpy(index_buffer_data->GetArrayData(), indexs, sizeof(indexs));

			LSPtr<LevRenderObjectAttribute> index_attribute = new LevRenderObjectAttribute(EROAT_UINT, sizeof(unsigned), index_buffer_data);

			LSPtr<LevRAttrRenderObjectAttributeBinder> attribute_binder = new LevRAttrRenderObjectAttributeBinder(4);
			attribute_binder->BindAttribute(0, vertex_attibute);
			attribute_binder->BindAttribute(1, normal_attribute);
			attribute_binder->SetIndexAttribute(index_attribute);

			LSPtr<LevSceneObject> plane_object = new LevSceneObject(ELSOT_DYNAMIC);
			plane_object->AddAttribute(TryCast<LevRAttrRenderObjectAttributeBinder, LevSceneObjectAttribute>(attribute_binder));

			out_plane_node.Reset(new LevSceneNode(plane_object));

			return true;
		}

		bool LevSceneUtil::GeneratePoints(const float* vertices, const float* normals,
		                                  unsigned count, LSPtr<LevSceneNode>& out_points_node)
		{
			LSPtr<LevRAttrRenderObjectAttributeBinder> attribute_binder = new LevRAttrRenderObjectAttributeBinder(count);

			LSPtr<RAIIBufferData> vertices_data = new RAIIBufferData(count * 3 * sizeof(float));
			memcpy(vertices_data->GetArrayData(), vertices, 3 * count * sizeof(float));

			LSPtr<LevRenderObjectAttribute> vertices_attribute = new LevRenderObjectAttribute(EROAT_FLOAT, 3 * sizeof(float), vertices_data);
			attribute_binder->BindAttribute(0, vertices_attribute);

			if (normals)
			{
				LSPtr<RAIIBufferData> normals_data = new RAIIBufferData(count * 3 * sizeof(float));
				memcpy(normals_data->GetArrayData(), normals, 3 * count * sizeof(float));

				LSPtr<LevRenderObjectAttribute> normals_attribute = new LevRenderObjectAttribute(EROAT_FLOAT, 3 * count * sizeof(float), normals_data);
				attribute_binder->BindAttribute(1, normals_attribute);
			}

			attribute_binder->SetPrimitiveType(EROPT_POINTS);

			LSPtr<LevSceneObject> point_object = new LevSceneObject(ELSOT_DYNAMIC);
			point_object->AddAttribute(attribute_binder);

			out_points_node.Reset(new LevSceneNode(point_object));
			return true;
		}

		bool LevSceneUtil::GenerateIdentityMatrixUniform(const char* uniform_name, LSPtr<LevNumericalUniform>& out_uniform)
		{
			static float identity_matrix[] =
			{
				1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f
			};

			out_uniform.Reset(new LevNumericalUniform(uniform_name, TYPE_FLOAT_MAT4));
			LSPtr<RAIIBufferData> identity_matrix_buffer_data = new RAIIBufferData(sizeof(identity_matrix));
			identity_matrix_buffer_data->SetArrayData(identity_matrix, sizeof(identity_matrix));
			out_uniform->SetData(identity_matrix_buffer_data);

			return true;
		}

	}
}