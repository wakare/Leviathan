#include "LevNormalScene.h"
#include "LevRAttrShaderProgram.h"
#include "LevRAttrUniform.h"
#include "LevSceneData.h"
#include "LevSceneTree.h"
#include "LevSceneNode.h"
#include "LevSceneObject.h"
#include "LevCamera.h"
#include "LevTimer.h"
#include "LevLight.h"
#include "LevPointLight.h"
#include "LevSceneDefaultShader_simple.h"
#include "LevRAttrUniformManager.h"

namespace Leviathan
{
	namespace Scene
	{
		LevNormalScene::LevNormalScene()
			: LevScene()
			, m_default_model_matrix(nullptr)
			, m_default_world_matrix(nullptr)
			, m_default_view_matrix(nullptr)
			, m_default_proj_matrix(nullptr)
			, m_camera_node(nullptr)
		{
			bool inited = false;

			inited = LevScene::Init(ELST_3D_SCENE);

			inited = _init_main_camera();
			LEV_ASSERT(inited);

			inited = _init_default_light();
			LEV_ASSERT(inited);

			inited = _init_root_node();
			LEV_ASSERT(inited);
		}

		void LevNormalScene::Update()
		{
			LevScene::Update();

			_update_camera();
		}

		bool LevNormalScene::_init_root_node()
		{
			auto& root_node = GetSceneData().GetSceneTree().GetRoot();

			// Add default pass
			LPtr<LevShaderProgram> default_shader_program = new LevShaderProgram;
			default_shader_program->m_frag_shader = default_frag_shader;
			default_shader_program->m_vert_shader = default_vertex_shader;

			LPtr<LevRAttrShaderProgram> default_program = new LevRAttrShaderProgram;
			default_program->SetShaderProgram(default_shader_program);

			root_node.GetNodeData()->AddAttribute(TryCast<LevRAttrShaderProgram, LevSceneObjectAttribute>(default_program));

			LPtr<LevRAttrUniformManager> uniform_manager = new LevRAttrUniformManager;
			root_node.GetNodeData()->AddAttribute(TryCast<LevRAttrUniformManager, LevSceneObjectAttribute>(uniform_manager));

			return true;
		}

		bool LevNormalScene::_init_main_camera()
		{
			// FOR DEBUG
			LPtr<LevCamera> pCamera = new LevCamera;
			pCamera->SetName("Main Camera");

			Eigen::Vector3f eye = { 0.0f, 0.0f, -10.0f };
			Eigen::Vector3f up = { 0.0f, 1.0f, 0.0f };
			Eigen::Vector3f lookAt = { 0.0f, 0.0f, 1.0f };
			auto _seted = pCamera->Set(eye.data(), lookAt.data(), up.data(), ANGLE_TO_RADIAN(120.0f), 1.0f, 0.01f, 10000.0f);
			LEV_ASSERT(_seted);

			m_camera_node = new LevSceneNode(TryCast<LevCamera, LevSceneObject>(pCamera));
			LEV_ASSERT(m_camera_node);

			LPtr<LevRAttrUniformManager> uniform_manager = new LevRAttrUniformManager;
			m_camera_node->GetNodeData()->AddAttribute(TryCast<LevRAttrUniformManager, LevSceneObjectAttribute>(uniform_manager));

			m_default_view_matrix = new LevRAttrUniform("viewMatrix", TYPE_FLOAT_MAT4);
			m_default_proj_matrix = new LevRAttrUniform("projMatrix", TYPE_FLOAT_MAT4);

			LPtr<RAIIBufferData> view_matrix_data = new RAIIBufferData(16 * sizeof(float));
			m_default_view_matrix->SetData(view_matrix_data);

			LPtr<RAIIBufferData> proj_matrix_data = new RAIIBufferData(16 * sizeof(float));
			m_default_proj_matrix->SetData(proj_matrix_data);

			uniform_manager->AddUniform(m_default_view_matrix);
			uniform_manager->AddUniform(m_default_proj_matrix);

			GetSceneData().AddSceneNode(m_camera_node);
			GetSceneData().RegisterToMainCamera(pCamera);
			
			return true;
		}

		bool LevNormalScene::_init_default_light()
		{
			LPtr<LevLight> pLight = new LevPointLight(ELSOT_LIGHT | ELSOT_DYNAMIC | ELSOT_UNRENDERABLE);
			pLight->SetName("Default light");

			pLight->AmbientColor({ 0.2f, 0.2f, 0.2f });
			pLight->DiffuseColor({ 0.5f, 0.5f, 0.5f });
			pLight->SpecularColor({ 1.0f, 1.0f, 1.0f });
			LPtr<LevSceneNode> pLightNode = new LevSceneNode(TryCast<LevLight, LevSceneObject>(pLight));
			GetSceneData().AddSceneNode(pLightNode);

			return true;
		}

		void LevNormalScene::_update_camera()
		{
			if (m_camera_node->GetNodeData()->GetState() == Scene::LevSceneObjectState::ELSOS_ADDED)
			{
				return;
			}

			LPtr<RAIIBufferData> view_matrix_data = new RAIIBufferData(16 * sizeof(float));
			view_matrix_data->SetArrayData(GetSceneData().GetMainCamera()->GetViewportMatrix().data(), 16 * sizeof(float));
			m_default_view_matrix->SetData(view_matrix_data);

			LPtr<RAIIBufferData> proj_matrix_data = new RAIIBufferData(16 * sizeof(float));
			proj_matrix_data->SetArrayData(GetSceneData().GetMainCamera()->GetProjectMatrix().data(), 16 * sizeof(float));
			m_default_proj_matrix->SetData(proj_matrix_data);

			m_camera_node->GetNodeData()->SetState(Scene::LevSceneObjectState::ELSOS_UPDATE);
		}
	}
}