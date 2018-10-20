#include "Scene.h"
#include <fstream>
#include <string>
#include <GL\glew.h>
#include <sstream>

#define PI 3.1415926f

Scene::Scene(RenderWindow& refRenderWindow) :
	m_refRenderWindow(refRenderWindow)
{
	m_pRenderWarpper = std::make_shared<RenderWrapper>(refRenderWindow.GetGLFWWindow());
	if (!m_pRenderWarpper)
	{
		throw "Scene::Scene(std::shared_ptr<RenderWindow> pRenderWindow) --> RenderWrapper init failed.";
		return;
	}

	float cameraEye[3] = { 0.0f, 0.0f ,-1.0f };
	float cameraLookAt[3] = { 0.0f, 0.0f, 0.0f};
	float cameraUp[3] = {0.0f, 1.0f, 0.0f};

	float fovy = PI * (45.0f / 180.0f);
	float aspect = (1.0f * m_refRenderWindow.GetWidth()) / m_refRenderWindow.GetHeight();
	float fNear = 0.01f;
	float fFar = 1000.0f;

	m_pCamera = std::make_shared<GLCamera>(cameraEye, cameraLookAt, cameraUp, fovy, aspect, fNear, fFar);
	if(!m_pCamera)
	{
		throw "Scene::Scene(std::shared_ptr<RenderWindow> pRenderWindow) --> GLCamera init failed.";
		return;
	}

	const char* pczVertexShaderPath = "ShaderSource\\VertexShader.glsl";
	const char* pczFragmentShaderPath = "ShaderSource\\FragmentShader.glsl";

	auto strVertexShader = _getShaderSource(pczVertexShaderPath);
	auto strFragmentShader = _getShaderSource(pczFragmentShaderPath);

	const char* pczVertexShaderSource = strVertexShader.c_str();
	const char* pczFragmentShaderSource = strFragmentShader.c_str();

	m_pShaderProgram = std::make_shared<GLShaderProgram>(&pczVertexShaderSource, &pczFragmentShaderSource, nullptr);
	if (!m_pShaderProgram)
	{
		throw "Scene::Scene(std::shared_ptr<RenderWindow> pRenderWindow) --> Create m_pShaderProgram failed.";
		return;
	}
	
	if (!m_pShaderProgram->Init())
	{
		throw "Scene::Scene(std::shared_ptr<RenderWindow> pRenderWindow) --> m_pShaderProgram Init failed.";
		return;
	}

	m_pMeshPass = std::make_shared<TriDObjectGLPass>(m_pShaderProgram, m_pCamera);
	if (!m_pMeshPass)
	{
		throw "Scene::Scene(std::shared_ptr<RenderWindow> pRenderWindow) --> Create m_pMeshPass failed.";
		return;
	}

	// Original Cube data
	float cube[252] =
	{
		// front			 // color
		-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 
		 0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f,
		-0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f,

		// up
		-0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f,
		0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f,
		0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f,
		0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f,

		// down
		-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f,

		// left
		-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f,
		-0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f,

		// right
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f,
		0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f,
		0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f,
		0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f,

		// back
		-0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f,
		 0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f,
		 0.5f,  0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f,
		 0.5f,  0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f,
		-0.5f,  0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f,
	};

	std::shared_ptr<GLObject> pCube = std::make_shared<TriDGLObject>(GL_TRIANGLES, cube, 36, TriDGLObject::VERTEX_ATTRIBUTE_XYZ | TriDGLObject::VERTEX_ATTRIBUTE_RGBA);
	m_pMeshPass->AddGLObject(pCube);

	m_pRenderWarpper->AddGLPass(m_pMeshPass);
};

void Scene::Update()
{
	m_pRenderWarpper->Render();
}

std::string Scene::_getShaderSource(const char* pczShaderSourcePath)
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
