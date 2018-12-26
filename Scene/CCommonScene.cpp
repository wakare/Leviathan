#include <fstream>
#include <string>
#include <GL\glew.h>
#include <sstream>
#include "CCommonScene.h"
#include "DynamicArray.h"
#include "CFileImportFactory.h"
#include "GeometryCalculator.h"
#include "DrawableNode.h"
#include "SOIL.h"
#include "PictureObject.h"



namespace Leviathan
{
	using namespace SceneBase;

	CCommonScene::CCommonScene(GLFWwindow* pRenderWindow, int width, int height) :
		IScene(),
		m_pGLFWWindow(pRenderWindow), 
		m_pRenderWarpper(nullptr), 
		m_pMeshPass(nullptr), 
		m_pShaderProgram(nullptr),
		m_pSceneGraph(nullptr)
	{
		m_pRenderWarpper = new RenderWrapper(pRenderWindow);

		if (!m_pRenderWarpper)
		{
			LeviathanOutStream << "[FATAL] RenderWrapper init failed." << std::endl;
			throw "RenderWrapper init failed.";
			return;
		}

		if (!_initCamera(width, height))
		{
			LeviathanOutStream << "[FATAL] Scene camera init failed." << std::endl;
			throw "Scene camera init failed.";
			return;
		}

		const char* pczVertexShaderPath = "ShaderSource\\VertexShader.glsl";
		const char* pczFragmentShaderPath = "ShaderSource\\FragmentShader.glsl";
		if (!_initShaderSource(pczVertexShaderPath, pczFragmentShaderPath))
		{
			LeviathanOutStream << "[FATAL] Scene ShaderSource init failed." << std::endl;
			throw "Scene ShaderSource init failed.";
			return;
		}

		m_pMeshPass = new TriDObjectGLPass(m_pShaderProgram, m_pCamera);
		if (!m_pMeshPass)
		{
			return;
		}
		//m_pMeshPass->SetCullFace(GL_CCW);

		m_pSceneGraph = new SceneGraph(TryCast<TriDObjectGLPass, GLPass>(m_pMeshPass));
		m_pRenderWarpper->AddGLPass(TryCast<TriDObjectGLPass, GLPass>(m_pMeshPass));
	};

	bool CCommonScene::_initSceneObject()
	{
		if (!_initLight())
		{
			LeviathanOutStream << "[ERROR] Init light failed." << std::endl;
			return false;
		}

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
		//pSceneNode->LoadModelFile("C:/Users/msi-cn/Documents/Visual Studio 2017/Projects/Leviathan/Leviathan/2b/lufeng.FBX");
		pSceneNode->LoadModelFile("C:/Users/msi-cn/Documents/Visual Studio 2017/Projects/Leviathan/Leviathan/Black_Dragon/Dragon_2.5_fbx.FBX");
		pSceneNode->SetWorldCoord(Vector3f(-100.0f, 100.0f, 10.0f));
		LPtr<DrawableNode<SceneNode>> pDentalNode = new DrawableNode<SceneNode>(pSceneNode->GetModelFileVec(), pSceneNode);

		auto& AABB = pSceneNode->GetModelFileVec()[0]->GetAABB();
		float RenderObjectAABBCenter[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
		if (!AABB.GetAABBCenter(RenderObjectAABBCenter))
		{
			LeviathanOutStream << "[ERROR] Get AABB failed." << std::endl;
			return false;
		}

		auto pDentalGLObjectVec = pDentalNode->GetGLObject();
		m_pSceneGraph->AddNode(TryCast<DrawableNode<SceneNode>, Node<SceneNode>>(pDentalNode), true);
		for (auto pDentalGLObject : pDentalGLObjectVec)
		{
			//LPtr<IGLMaterial> pModelMaterial = new GLCommonMaterial({ 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f });
			//pDentalGLObject->SetMaterial(pModelMaterial);
			pDentalGLObject->SetLightEnable(true);

			// Set camera lookAt
			m_pCamera->LookAt(Vector4f(RenderObjectAABBCenter) * pDentalNode->GetNodeData()->GetWorldTransform(), AABB.GetAABBRadius() * 2.0f);
			pDentalGLObject->SetModelMatrix(pDentalNode->GetNodeData()->GetWorldTransform().GetInverseMatrix());
		}

		// m_pSceneGraph->AddDrawableNodeToSceneRenderPass(m_pSceneGraph->GetRootNode());
		m_pSceneGraph->AddDrawableNodeToSceneOcTree(m_pSceneGraph->GetRootNode());
		m_pSceneGraph->AddSceneOcTreeToGLPass();

		return true;
	}

	bool CCommonScene::_initShaderSource(const char* pczVertexShaderPath, const char* pczFragmentShaderPath)
	{
		auto strVertexShader = _getShaderSource(pczVertexShaderPath);
		auto strFragmentShader = _getShaderSource(pczFragmentShaderPath);

		const char* pczVertexShaderSource = strVertexShader.c_str();
		const char* pczFragmentShaderSource = strFragmentShader.c_str();

		m_pShaderProgram = new GLShaderProgram(&pczVertexShaderSource, &pczFragmentShaderSource, nullptr);
		if (!m_pShaderProgram)
		{
			return false;
		}

		if (!m_pShaderProgram->Init())
		{
			return false;
		}

		return true;
	}

	bool CCommonScene::_initCamera(unsigned uWidth, unsigned uHeight)
	{
		float cameraEye[3] = { 0.0f, 0.0f, -10.0f };
		float cameraLookAt[3] = { 0.0f, 0.0f, 0.0f };
		float cameraUp[3] = { 0.0f, 1.0f, 0.0f };

		float fovy = PI_FLOAT * (45.0f / 180.0f);
		float fAspect = (1.0f * uWidth) / uHeight;
		float fNear = 0.01f;
		float fFar = 10000.0f;

		m_pCamera = new GLCamera(cameraEye, cameraLookAt, cameraUp, fovy, fAspect, fNear, fFar);
		if (!m_pCamera)
		{
			throw "Exception";
			return false;
		}

		return true;
	}

	bool CCommonScene::_initLight()
	{
		LPtr<GLLight> light = new GLLight({ -100.0f, 100.0f, 10.0f }, { 0.5f, 0.5f, 0.5f }, { 0.8f, 0.8f, 0.8f }, { 1.0f, 1.0f, 1.0f });
		m_pMeshPass->AddGLLight(light);
		m_pLights.push_back(light);
		
		return true;
	}

	CCommonScene::~CCommonScene()
	{

	}

	void CCommonScene::Update()
	{
		static bool bFirstUpdate = true;
		if (bFirstUpdate)
		{
			if (!_initSceneObject())
			{
				LeviathanOutStream << "[ERROR] Init scene object failed." << std::endl;
			}

			bFirstUpdate = false;
		}

		m_pRenderWarpper->Render();
	}

	std::string CCommonScene::_getShaderSource(const char* pczShaderSourcePath)
	{
		std::ifstream shaderSourceFileStream(pczShaderSourcePath, std::ios::in);
		if (!shaderSourceFileStream.is_open())
		{
			throw "std::string Scene::_getShaderSource(const char* pczShaderSourcePath) --> Invalid ShaderSource paths.";
			return std::string();
		}

		std::stringstream strStream;
		strStream << shaderSourceFileStream.rdbuf();

		return strStream.str();
	}
}