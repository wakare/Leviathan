#include "TriDObjectGLPass.h"
#include "GlobalDef.h"
namespace Leviathan
{
	bool TriDObjectGLPass::Init()
	{
		if (m_bInited)
		{
			return true;
		}

		EXIT_GET_FALSE(m_pGLShaderProgram);
		EXIT_GET_FALSE(m_pGLShaderProgram->Init());

		// Add matrix uniform to shaderProgram
		LPtr<GLUniform> viewMatrixUniform = new GLUniform("viewMatrix", GLUniform::TYPE_FLOAT_MAT4);
		auto viewMatrix = m_mainCamera->GetViewportTransformMatrix();
		viewMatrixUniform->SetData(viewMatrix.GetData(), viewMatrix.GetDataSize());
		if (!m_pGLShaderProgram->AddUniform(viewMatrixUniform))
		{
			throw "TriDObjectGLPass::Init() failed.";
			return false;
		}

		LPtr<GLUniform> PerspectiveMatrixUniform = new GLUniform("projMatrix", GLUniform::TYPE_FLOAT_MAT4);
		auto projMatrix = m_mainCamera->GetPerspectiveTransformMatrix();
		PerspectiveMatrixUniform->SetData(projMatrix.GetData(), projMatrix.GetDataSize());
		if (!m_pGLShaderProgram->AddUniform(PerspectiveMatrixUniform))
		{
			throw "TriDObjectGLPass::Init() failed.";
			return false;
		}

		m_bInited = true;
		return true;
	}

	void TriDObjectGLPass::Render()
	{
		// Call PreCallBack
		for (auto& process : m_PreRenderCallBacks)
		{
			process();
		}

		// Set renderType
		glEnable(GL_DEPTH_TEST);
		glPolygonMode(GL_FRONT_AND_BACK, m_nPolygonMode);

		// Set GLProgram
		auto program = m_pGLShaderProgram->GetShaderProgram();
		glUseProgram(program);
		m_pGLShaderProgram->SetGLUniformState();

		// Set viewMatrix
		_updateCameraMatrixUniform(program);

		// Render each GLObject
		for (auto& Object : m_GLObjects)
		{
			Object->Render(program);
		}

		// ResetProgram
		glUseProgram(0);
		glDisable(GL_DEPTH_TEST);

		// Call PostCallBack
		for (auto& process : m_PostRenderCallBacks)
		{
			process();
		}
	}

	void TriDObjectGLPass::_updateCameraMatrixUniform(GLuint shaderProgram)
	{
		auto pViewMatrixUniform = m_pGLShaderProgram->GetUniformByName("viewMatrix");
		if (pViewMatrixUniform == nullptr)
		{
			throw "TriDObjectGLPass::_updateCameraMatrixUniform(GLuint shaderProgram) --> GetUniform failed.";
			return;
		}

		auto viewMatrix = m_mainCamera->GetViewportTransformMatrix();
		pViewMatrixUniform->SetData(viewMatrix.GetData(), viewMatrix.GetDataSize());

		auto pPerspectiveMatrixUniform = m_pGLShaderProgram->GetUniformByName("projMatrix");
		if (pPerspectiveMatrixUniform == nullptr)
		{
			throw "TriDObjectGLPass::_updateCameraMatrixUniform(GLuint shaderProgram) --> GetUniform failed.";
			return;
		}

		auto PerspectiveMatrix = m_mainCamera->GetPerspectiveTransformMatrix();
		pPerspectiveMatrixUniform->SetData(PerspectiveMatrix.GetData(), PerspectiveMatrix.GetDataSize());
	}
}