#include "TriDScene.h"
#include "SceneNode.h"
#include "DrawableNode.h"
#include "SceneGraph.h"

namespace Leviathan
{
	TriDScene::TriDScene(GLFWwindow* pRenderWindow, int width, int height):
		CommonScene(pRenderWindow, width, height)
	{

	}

	bool TriDScene::_firstUpdate()
	{
		// Init light
		EXIT_GET_FALSE(_initLight());

		if (!_initSceneObject())
		{
			LeviathanOutStream << "[ERROR] Init scene object failed." << std::endl;
		}

		_resetCamera();

		return true;
	}

	bool TriDScene::_initSceneObject()
	{
		// 		float cubeAABB[6] =
// 		{
// 			10.0f, 10.0f, 10.0f,
// 			20.0f, 20.0f, 20.0f,
// 		};
// 
// 		LPtr<GLObject> pCubeGLObject = _convertAABBtoGLObject(cubeAABB);
// 		pCubeGLObject->SetLightEnable(true);
// 		LPtr<GLCommonMaterial> pMaterial = new GLCommonMaterial({ 0.5f, 0.5f, 0.5f }, { 0.8f, 0.8f, 0.8f }, {1.0f, 1.0f, 1.0f});
// 
// 		// Load file as texture 
// 		PictureObject texture("container.jpg");

// 		pMaterial->AddTexture2D(new GLTexture2D(texture.m_pData, texture.m_nWidth, texture.m_nHeight));
// 		pCubeGLObject->SetMaterial(TryCast<GLCommonMaterial, IGLMaterial>(pMaterial));
// 
// 		LPtr<DrawableNode<SceneNode>> pCubeNode = new DrawableNode<SceneNode>(pCubeGLObject, new SceneNode());
// 		m_pSceneGraph->AddNode(TryCast<DrawableNode<SceneNode>, Node<SceneNode>>(pCubeNode), true);
// 		m_pCamera->LookAt({ 15.0f, 15.0f, 15.0f });

		auto pSceneNode = LPtr<SceneNode>(new SceneNode());
		//pSceneNode->LoadModelFile("C:/Users/msi-cn/Documents/Visual Studio 2017/Projects/Leviathan/src/Leviathan/2b/lufeng.FBX");
		pSceneNode->LoadModelFile("C:/Users/wangjie/Documents/Leviathan/src/Leviathan/Black_Dragon/Dragon_2.5_fbx.FBX");
		pSceneNode->SetWorldCoord(Vector3f(-100.0f, 100.0f, 10.0f));
		LPtr<DrawableNode<SceneNode>> pDentalNode = new DrawableNode<SceneNode>(pSceneNode->GetMeshVec(), pSceneNode);

		auto& AABB = pSceneNode->GetMeshVec()[0]->GetAABB();
		float RenderObjectAABBCenter[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
		if (!AABB.GetAABBCenter(RenderObjectAABBCenter))
		{
			LeviathanOutStream << "[ERROR] Get AABB failed." << std::endl;
			return false;
		}

		auto pDentalGLObjectVec = pDentalNode->GetGLObject();
		m_pSceneGraph->AddNode(TryCast<DrawableNode<SceneNode>, Node<SceneNode>>(pDentalNode));
		for (auto pDentalGLObject : pDentalGLObjectVec)
		{
			pDentalGLObject->SetLightEnable(true);
			// Set camera lookAt
			pDentalGLObject->SetModelMatrix(pDentalNode->GetNodeData()->GetWorldTransform().GetInverseMatrix());
		}

		_sceneGraphUpdate();

		// Set camera lookAt
		_resetCamera();

		return true;
	}

}