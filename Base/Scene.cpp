#include "Scene.h"
#include <fstream>
#include <string>
#define GLEW_STATIC
#include <GL\glew.h>

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
	if(m_pCamera)
	{
		throw "Scene::Scene(std::shared_ptr<RenderWindow> pRenderWindow) --> GLCamera init failed.";
		return;
	}

	const char* pczVertexShaderPath = "ShaderSource\\VertexShader.glsl";
	const char* pczFragmentShaderPath = "ShaderSource\\FragmentShader.glsl";

	const char* pczVertexShaderSource = _getShaderSource(pczVertexShaderPath).c_str();
	const char* pczFragmentShaderSource = _getShaderSource(pczFragmentShaderPath).c_str();

	m_pShaderProgram = std::make_shared<GLShaderProgram>(&pczVertexShaderSource, &pczFragmentShaderSource);
	if (!m_pShaderProgram)
	{
		throw "Scene::Scene(std::shared_ptr<RenderWindow> pRenderWindow) --> Create m_pShaderProgram failed.";
		return;
	}

	m_pMeshPass = std::make_shared<TriDObjectGLPass>(m_pShaderProgram);
	if (!m_pMeshPass)
	{
		throw "Scene::Scene(std::shared_ptr<RenderWindow> pRenderWindow) --> Create m_pMeshPass failed.";
		return;
	}

	/*m_pMeshPass->AddPreProcess([&]()
	{
		gluLookAt(
			m_pCamera->m_eye[0], m_pCamera->m_eye[1], m_pCamera->m_eye[2],
			m_pCamera->m_look[0], m_pCamera->m_look[1], m_pCamera->m_look[2],
			m_pCamera->m_up[0], m_pCamera->m_up[1], m_pCamera->m_up[2]
		);

		gluPerspective(m_pCamera->m_fovy, m_pCamera->m_aspect, m_pCamera->m_zNear, m_pCamera->m_zFar);
	});*/
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

	std::string strResult;
	std::string strline;
	while (std::getline(shaderSourceFileStream, strline))
	{
		strResult.append(strline);
	}

	return strResult;
}
