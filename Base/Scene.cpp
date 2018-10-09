#include "Scene.h"
#include <fstream>
#include <string>
#define GLEW_STATIC
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

	float cameraEye[3];
	float cameraLook[3];
	float cameraUp[3];

	float fovy = PI / 45.0f;
	float aspect = (1.0f * m_refRenderWindow.GetWidth()) / m_refRenderWindow.GetWidth();
	float fNear = 0.01f;
	float fFar = 1000.0f;

	m_pCamera = std::make_shared<GLCamera>(cameraEye, cameraLook, cameraUp, fovy, aspect, fNear, fFar);
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

	m_pMeshPass = std::make_shared<TriDObjectGLPass>(m_pShaderProgram);
	if (!m_pMeshPass)
	{
		throw "Scene::Scene(std::shared_ptr<RenderWindow> pRenderWindow) --> Create m_pMeshPass failed.";
		return;
	}

	// Original Cube data
	float cube[72] =
	{
		// front
		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,

		// up
		-0.5f, 0.5f, -0.5f,
		0.5f, 0.5f, -0.5f, 
		0.5f, 0.5f, 0.5f,
		-0.5f, 0.5f, 0.5f,

		// down
		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f, 
		-0.5f, -0.5f,  0.5f,

		// left
		-0.5f, -0.5f, -0.5f,
		-0.5f, 0.5f, -0.5f,
		-0.5f, 0.5f, 0.5f,
		-0.5f, -0.5f, 0.5f,

		// right
		0.5f, -0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		0.5f,  0.5f,  0.5f,
		0.5f, -0.5f,  0.5f,

		// back
		-0.5f, -0.5f, 0.5f,
		 0.5f, -0.5f, 0.5f,
		 0.5f,  0.5f, 0.5f,
		-0.5f,  0.5f, 0.5f,
	};

	GLfloat vertices[] = {
		0.5f,  0.5f, -0.5f,  // Top Right
		0.5f, -0.5f, 0.5f,  // Bottom Right
		-0.5f, -0.5f, 0.0f,  // Bottom Left
	};

	std::shared_ptr<GLObject> Cube = std::make_shared<TriDGLObject>(GL_TRIANGLES, vertices, 3, TriDGLObject::VERTEX_ATTRIBUTE_XYZ);
	m_pMeshPass->AddGLObject(Cube);

	m_pRenderWarpper->AddGLPass(m_pMeshPass);
	//m_pMeshPass->AddPreProcess([&]()
	//{
	//	/*gluLookAt(
	//		m_pCamera->m_eye[0], m_pCamera->m_eye[1], m_pCamera->m_eye[2],
	//		m_pCamera->m_look[0], m_pCamera->m_look[1], m_pCamera->m_look[2],
	//		m_pCamera->m_up[0], m_pCamera->m_up[1], m_pCamera->m_up[2]
	//	);

	//	gluPerspective(m_pCamera->m_fovy, m_pCamera->m_aspect, m_pCamera->m_zNear, m_pCamera->m_zFar);*/
	//});
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
