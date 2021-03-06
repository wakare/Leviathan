#include "LevNormalScene.h"
#include "LevRAttrShaderProgram.h"
#include "LevNumericalUniform.h"
#include "LevSceneData.h"
#include "LevSceneTree.h"
#include "LevSceneNode.h"
#include "LevSceneObject.h"
#include "LevCamera.h"
#include "LevSceneDefaultShader_phong.h"
#include "LevRAttrUniformManager.h"
#include "LevRAttrRenderStateManager.h"
#include "LevRenderStateDepthFunc.h"

namespace Leviathan
{
	namespace Scene
	{
		LevNormalScene::LevNormalScene()
			: LevScene()
			, m_camera_node(nullptr)
			, m_default_view_matrix(nullptr)
			, m_default_proj_matrix(nullptr)
		{
			bool inited = false;

			inited = LevScene::Init(ELST_3D_SCENE);

			inited = _init_main_camera();
			LEV_ASSERT(inited);

			inited = _init_root_node();
			LEV_ASSERT(inited);

			inited = _init_default_light_root_node();
			LEV_ASSERT(inited);
		}

		void LevNormalScene::Update()
		{
			LevScene::Update();

			_update_camera();
		}

		Leviathan::LSPtr<Leviathan::Scene::LevSceneNode> LevNormalScene::GetLightRootNode()
		{
			return m_light_root_node;
		}

		bool LevNormalScene::_init_root_node()
		{
			auto& root_node = GetSceneData().GetSceneTree().GetRoot();

			// Add default pass
			LSPtr<LevShaderProgram> default_shader_program = new LevShaderProgram;
			default_shader_program->m_frag_shader = default_frag_shader;
			default_shader_program->m_vert_shader = default_vertex_shader;

			LSPtr<LevRAttrShaderProgram> default_program = new LevRAttrShaderProgram;
			default_program->SetShaderProgram(default_shader_program);

			root_node.GetNodeData()->AddAttribute(TryCast<LevRAttrShaderProgram, LevSceneObjectAttribute>(default_program));

			LSPtr<LevRAttrUniformManager> uniform_manager = new LevRAttrUniformManager;
			root_node.GetNodeData()->AddAttribute(TryCast<LevRAttrUniformManager, LevSceneObjectAttribute>(uniform_manager));

			/*
				Set default render state.
			*/
			LSPtr<LevRAttrRenderStateManager> render_state_manager = new LevRAttrRenderStateManager;
			root_node.GetNodeData()->AddAttribute(TryCast<LevRAttrRenderStateManager, LevSceneObjectAttribute>(render_state_manager));
			render_state_manager->UpdateRenderState(new LevRenderStateDepthFunc(ELDF_LESS));

			return true;
		}

		bool LevNormalScene::_init_main_camera()
		{
			// FOR DEBUG
			LSPtr<LevCamera> pCamera = new LevCamera;
			pCamera->SetName("Main Camera");

			Eigen::Vector3f eye = { 0.0f, 0.0f, -10.0f };
			Eigen::Vector3f up = { 0.0f, 1.0f, 0.0f };
			Eigen::Vector3f lookAt = { 0.0f, 0.0f, 1.0f };
			auto _seted = pCamera->Set(eye.data(), lookAt.data(), up.data(), ANGLE_TO_RADIAN(60.0f), 1.0f, 0.01f, 10000.0f);
			LEV_ASSERT(_seted);

			m_camera_node = new LevSceneNode(TryCast<LevCamera, LevSceneObject>(pCamera));
			LEV_ASSERT(m_camera_node);

			LSPtr<LevRAttrUniformManager> uniform_manager = new LevRAttrUniformManager;
			m_camera_node->GetNodeData()->AddAttribute(TryCast<LevRAttrUniformManager, LevSceneObjectAttribute>(uniform_manager));

			m_default_view_matrix = new LevNumericalUniform("viewMatrix", TYPE_FLOAT_MAT4);
			m_default_proj_matrix = new LevNumericalUniform("projMatrix", TYPE_FLOAT_MAT4);

			LSPtr<RAIIBufferData> view_matrix_data = new RAIIBufferData(16 * sizeof(float));
			m_default_view_matrix->SetData(view_matrix_data);

			LSPtr<RAIIBufferData> proj_matrix_data = new RAIIBufferData(16 * sizeof(float));
			m_default_proj_matrix->SetData(proj_matrix_data);

			uniform_manager->AddUniform(TryCast<LevNumericalUniform, ILevUniform>(m_default_view_matrix));
			uniform_manager->AddUniform(TryCast<LevNumericalUniform, ILevUniform>(m_default_proj_matrix));

			GetSceneData().RegisterToMainCamera(pCamera, m_camera_node);
			
			return true;
		}

		bool LevNormalScene::_init_default_light_root_node()
		{
			LSPtr<LevSceneObject> light_object = new LevSceneObject(ELSOT_DYNAMIC);
			m_light_root_node = new LevSceneNode(light_object);

			GetSceneData().AddSceneNodeToRoot(m_light_root_node);
			return true;
		}

		void LevNormalScene::_update_camera()
		{
			if (m_camera_node->GetNodeData()->GetState() == Scene::LevSceneObjectState::ELSOS_ADDED)
			{
				return;
			}

			LSPtr<RAIIBufferData> view_matrix_data = new RAIIBufferData(16 * sizeof(float));
			view_matrix_data->SetArrayData(GetSceneData().GetMainCamera()->GetViewportMatrix().data(), 16 * sizeof(float));
			m_default_view_matrix->SetData(view_matrix_data);

			LSPtr<RAIIBufferData> proj_matrix_data = new RAIIBufferData(16 * sizeof(float));
			proj_matrix_data->SetArrayData(GetSceneData().GetMainCamera()->GetProjectMatrix().data(), 16 * sizeof(float));
			m_default_proj_matrix->SetData(proj_matrix_data);

			m_camera_node->GetNodeData()->SetState(Scene::LevSceneObjectState::ELSOS_UPDATE);
		}
	}
}