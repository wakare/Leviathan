#include <fstream>
#include <string>
#include <sstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Camera.h"
#include "GLLight.h"
#include "CommonScene.h"
#include "DynamicArray.h"
#include "CFileImportFactory.h"
#include "GeometryCalculator.h"
#include "DrawableNode.h"
#include "SOIL.h"
#include "PictureObject.h"
#include "SceneNode.h"
#include "CMesh.h"
#include "RenderWrapper.h"
#include "TriDObjectGLPass.h"
#include "TriDGLObject.h"
#include "GLShaderProgram.h"
#include "IMesh.h"
#include "SceneGraph.h"
#include "SceneHelper.h"
#include "SceneLogicDataSet.h"

namespace Leviathan
{
	CommonScene::CommonScene(GLFWwindow* pRenderWindow, int width, int height) :
		IScene(),
		m_pGLFWWindow(pRenderWindow), 
		m_pRenderWrapper(nullptr), 
		m_pMeshPass(nullptr), 
		m_pShaderProgram(nullptr),
		m_pSceneLogicData(nullptr)
	{
		m_pRenderWrapper = new RenderWrapper(pRenderWindow);

		if (!m_pRenderWrapper)
		{
			LeviathanOutStream << "[FATAL] RenderWrapper init failed." << std::endl;
			throw "exception";
			return;
		}

		if (!_initCamera(width, height))
		{
			LeviathanOutStream << "[FATAL] Scene camera init failed." << std::endl;
			throw "exception";
			return;
		}

		const char* pczVertexShaderPath = "ShaderSource\\VertexShader.glsl";
		const char* pczFragmentShaderPath = "ShaderSource\\FragmentShader.glsl";
		if (!SceneHelper::InitShaderSource(pczVertexShaderPath, pczFragmentShaderPath, m_pShaderProgram))
		{
			LeviathanOutStream << "[FATAL] Scene ShaderSource init failed." << std::endl;
			throw "exception";
			return;
		}

		m_pMeshPass = new TriDObjectGLPass(m_pShaderProgram, m_pCamera);
		if (!m_pMeshPass) return; 

		m_pRenderWrapper->AddGLPass(TryCast<TriDObjectGLPass, GLPass>(m_pMeshPass));
		m_pSceneLogicData = new SceneLogicDataSet(TryCast<TriDObjectGLPass, GLPass>(m_pMeshPass));
	};

	CommonScene::~CommonScene()
	{

	}

	Leviathan::Camera& CommonScene::GetCamera()
	{
		return *m_pCamera;
	}

	const std::vector<Leviathan::LPtr<Leviathan::GLLight>>& CommonScene::GetLightVec() const
	{
		return m_pLights;
	}

	bool CommonScene::_firstUpdate()
	{
		return true;
	}

	bool CommonScene::_initSceneObject()
	{
		return true;
	}

	bool CommonScene::_initCamera(unsigned uWidth, unsigned uHeight)
	{
		float cameraEye[3] = { 0.0f, 0.0f, -10.0f };
		float cameraLookAt[3] = { 0.0f, 0.0f, 0.0f };
		float cameraUp[3] = { 0.0f, 1.0f, 0.0f };

		float fovy = PI_FLOAT * (45.0f / 180.0f);
		float fAspect = (1.0f * uWidth) / uHeight;
		float fNear = 0.01f;
		float fFar = 100000.0f;

		m_pCamera = new Camera(cameraEye, cameraLookAt, cameraUp, fovy, fAspect, fNear, fFar);
		if (!m_pCamera)
		{
			throw "Exception";
			return false;
		}

		return true;
	}

	bool CommonScene::_initLight()
	{
		LPtr<GLLight> light = new GLLight({ -100.0f, 100.0f, 10.0f }, { 0.5f, 0.5f, 0.5f },
			{ 0.8f, 0.8f, 0.8f }, { 1.0f, 1.0f, 1.0f });

		m_pMeshPass->AddGLLight(light);
		m_pLights.push_back(light);
		return true;
	}

	void CommonScene::_resetCamera(float* coord/* = nullptr*/, float fDistance /* = -1.0f*/)
	{
		if (!coord)
		{
			auto AABB = m_pSceneLogicData->GetAABB();
			float center[3];
			AABB.GetAABBCenter(center);

			m_pCamera->LookAt(Vector4f(center), fDistance);
		}
		else
		{
			m_pCamera->LookAt(Vector4f(coord), fDistance);
		}
	}

	Leviathan::SceneLogicDataSet& CommonScene::GetSceneData()
	{
		return *m_pSceneLogicData;
	}

	void CommonScene::Update()
	{
		static bool bFirstUpdate = true;
		if (bFirstUpdate)
		{
			_firstUpdate();
			bFirstUpdate = false;
		}

		m_pSceneLogicData->Update();
		m_pRenderWrapper->Render();
	}

	bool CommonScene::Clear()
	{
		m_pMeshPass->ClearGLObject();
		m_pSceneLogicData = new SceneLogicDataSet(TryCast<TriDObjectGLPass, GLPass>(m_pMeshPass));
		return true;
	}

}