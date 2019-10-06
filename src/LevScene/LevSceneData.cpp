#include "LevSceneData.h"
#include "LevSceneTree.h"
#include "LevSceneNode.h"
#include "LevCamera.h"
#include "LevMeshObject.h"
#include "LevLight.h"
#include "LevSceneObject.h"
#include "LevRAttrShaderProgram.h"
#include "LevNumericalUniform.h"

namespace Leviathan
{
	namespace Scene
	{
		LevSceneData::LevSceneData()
			: m_pSceneTree(new LevSceneTree)
			, m_modified(true)
			, m_main_camera(nullptr)
			, m_main_camera_node(nullptr)
		{
			m_modifiedCallback = [this](const LevSceneObject& obj)
			{
				m_modified = true;
			};
		}

		LevSceneTree & LevSceneData::GetSceneTree()
		{
			return *m_pSceneTree;
		}

		const Leviathan::Scene::LevSceneTree& LevSceneData::GetSceneTree() const
		{
			return *m_pSceneTree;
		}

		bool LevSceneData::HasModified() const
		{
			return m_modified;
		}

		void LevSceneData::SetModified()
		{
			m_pSceneTree->SetObjModified();
		}

		void LevSceneData::ResetUnModified()
		{
			m_pSceneTree->ResetObjUnModified();
			m_modified = false;
		}

		void LevSceneData::UpdateWorldTransform()
		{
			m_pSceneTree->UpdateWorldCoord();
		}

		void LevSceneData::UpdateTimer()
		{
			m_pSceneTree->UpdateTimer();
		}

		void LevSceneData::DoUserUpdateCallback()
		{
			m_pSceneTree->DoUserUpdataCallback();
		}

		void LevSceneData::RegisterToMainCamera(LSPtr<LevCamera> camera, LSPtr<LevSceneNode> camera_node)
		{
			m_main_camera = camera;

			m_main_camera_node = camera_node;
			AddSceneNodeToRoot(m_main_camera_node);
		}

		LSPtr<LevSceneNode> LevSceneData::GetMainCameraNode()
		{
			return m_main_camera_node;
		}

		LevSceneNode& LevSceneData::GetSceneRootNode()
		{
			return m_pSceneTree->GetRoot();
		}

		LSPtr<LevCamera> LevSceneData::GetMainCamera()
		{
			return m_main_camera;
		}

		bool LevSceneData::SetMainCamera(LSPtr<LevCamera> camera)
		{
			EXIT_IF_FALSE(camera);
			m_main_camera = camera;
			return true;
		}

		bool LevSceneData::AddSceneNodeToRoot(LSPtr<LevSceneNode> pNode)
		{
			pNode->GetNodeData()->SetModifiedCallback(m_modifiedCallback);
			EXIT_IF_FALSE(m_pSceneTree->AddNodeToParent(pNode));
			return true;
		}

		bool LevSceneData::AddSceneNodeToParent(LSPtr<LevSceneNode> pNode, LSPtr<LevSceneNode> parent_node)
		{
			pNode->GetNodeData()->SetModifiedCallback(m_modifiedCallback);
			EXIT_IF_FALSE(m_pSceneTree->AddNodeToParent(pNode, parent_node));
			return true;
		}

		void LevSceneData::RemoveAllRenderables()
		{

		}

		void LevSceneData::UpdateNodeState()
		{
			m_pSceneTree->UpdateNodeState();
		}
}
}