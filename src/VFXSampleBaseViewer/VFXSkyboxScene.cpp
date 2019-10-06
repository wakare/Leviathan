#include "VFXSkyboxScene.h"
#include "PictureObject.h"
#include "LevSceneNode.h"
#include "LevSceneData.h"
#include "LevSceneUtil.h"
#include "LevRAttrShaderProgram.h"
#include "SkyboxProgram.h"
#include "LevRAttrDepthFunc.h"

namespace Leviathan
{
	namespace Viewer
	{
		VFXSkyBoxScene::VFXSkyBoxScene()
			: m_skybox_uniform(nullptr)
			, m_texture_data(nullptr)
			, m_root_node(nullptr)
		{
			const LSPtr<LevSceneObject> root_object = new LevSceneObject(ELSOT_EMPTY);
			m_root_node.Reset(new LevSceneNode(root_object));

			GetSceneData().AddSceneNodeToRoot(m_root_node);

			LSPtr<LevShaderProgram> shader_program = new LevShaderProgram;
			shader_program->m_vert_shader = skybox_vert;
			shader_program->m_frag_shader = skybox_frag;

			LSPtr<LevRAttrShaderProgram> attr_shader_program = new LevRAttrShaderProgram;
			attr_shader_program->SetShaderProgram(shader_program);

			GetSceneData().GetSceneRootNode().GetNodeData()->UpdateAttribute(attr_shader_program);

			const bool _texture_loaded = _load_skybox_texture("Resource\\skybox");
			assert(_texture_loaded);

			const bool _inited = _init_scene();
			assert(_inited);
		}

		bool VFXSkyBoxScene::_load_skybox_texture(const char* skybox_texture_folder_path)
		{
			const std::string root = skybox_texture_folder_path;

			const std::string path[] =
			{
				root + "/right.jpg",
				root + "/left.jpg",
				root + "/top.jpg",
				root + "/bottom.jpg",
				root + "/front.jpg",
				root + "/back.jpg",
			};

			pictures.resize(6);
			m_texture_data = new RAIIBufferData(6 * sizeof(void*));

			int width = -1;
			int height = -1;

			for (unsigned i = 0; i < 6; ++i)
			{
				pictures[i].Reset(new PictureObject(path[i].c_str()));

				char* current_pointer = static_cast<char*>(m_texture_data->GetArrayData()) + i * sizeof(void*);
				memcpy(current_pointer, &pictures[i]->m_pData, sizeof(void*));

				if (width < 0 && height < 0)
				{
					width = pictures[i]->m_nWidth;
					height = pictures[i]->m_nHeight;
				}
				else
				{
					if (width != pictures[i]->m_nWidth || height != pictures[i]->m_nHeight)
					{
						throw "";
					}
				}
			}
			
			m_skybox_uniform = new LevTextureUniform("SKY_BOX_TEXTURE");
			LSPtr<LevTextureObject> cube_map_object = new LevTextureObject(Scene::ELTT_CUBEMAP_COLOR_TEXTURE, width, height, 1, m_texture_data);
			m_skybox_uniform->SetUniformData(cube_map_object);

			m_root_node->GetNodeData()->AddUniform(m_skybox_uniform.To<ILevUniform>());

			LSPtr<LevSceneNode> cube_object = nullptr;

			const float cube_data[] =
			{
				0.0f, 0.0f, 0.0f
			};

			LevSceneUtil::GenerateCube(cube_data, 1.0f, cube_object);
			m_root_node->AddChild(cube_object);

			LSPtr<LevRAttrDepthFunc> depth = new LevRAttrDepthFunc(ELDFP_ALWAYS);
			cube_object->GetNodeData()->AddAttribute(depth);

			return true;
		}

		bool VFXSkyBoxScene::_init_scene()
		{
			LSPtr<LevSceneNode> sphere_node = nullptr;

			const float sphere_center[] = {0.0, 0.0, 0.0};
			LevSceneUtil::GenerateBallNode(sphere_center, 1.0f, sphere_node);

			LSPtr<LevSceneNode> scene_node = nullptr;
			LevSceneUtil::GenerateEmptySceneNode(scene_node);
			m_root_node->AddChild(scene_node);

			LSPtr<LevRAttrShaderProgram> attr_shader_program = new LevRAttrShaderProgram;
			LSPtr<LevShaderProgram> shader_program = new LevShaderProgram;
			shader_program->m_vert_shader = reflect_vert;
			//shader_program->m_frag_shader = reflect_frag;
			shader_program->m_frag_shader = refract_frag;

			attr_shader_program->SetShaderProgram(shader_program);
			scene_node->GetNodeData()->AddAttribute(attr_shader_program);
			scene_node->AddChild(sphere_node);
			scene_node->GetNodeData()->AddUniform(m_skybox_uniform.To<ILevUniform>());

			scene_node->GetNodeData()->AddUniform(m_default_view_matrix.To<ILevUniform>());
			scene_node->GetNodeData()->AddUniform(m_default_proj_matrix.To<ILevUniform>());

			LSPtr<LevNumericalUniform> model_matrix_uniform = nullptr;
			LSPtr<LevNumericalUniform> world_matrix_uniform = nullptr;
			LevSceneUtil::GenerateIdentityMatrixUniform("modelMatrix", model_matrix_uniform);
			LevSceneUtil::GenerateIdentityMatrixUniform("worldMatrix", world_matrix_uniform);

			scene_node->GetNodeData()->AddUniform(model_matrix_uniform.To<ILevUniform>());
			scene_node->GetNodeData()->AddUniform(world_matrix_uniform.To<ILevUniform>());

			Scene::LevSceneObjUpdated updater = [&](LevSceneObject&)
			{
				GetSceneData().GetMainCamera()->MouseRotate(0.0f, 0.01f);
			};
			scene_node->GetNodeData()->SetUpdatedCallback(updater);

			return true;
		}
	}
}
