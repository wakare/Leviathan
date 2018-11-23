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
		LPtr<GLUniform> modelMatrixUniform = new GLUniform("modelMatrix", GLUniform::TYPE_FLOAT_MAT4);
		//auto viewMatrix = m_pMainCamera->GetViewportTransformMatrix();
		Matrix4f modelMatrix = Matrix4f::GetIdentityMatrix();
		modelMatrixUniform->SetData(modelMatrix.GetData(), modelMatrix.GetDataSize());
		if (!m_pGLShaderProgram->AddUniform(modelMatrixUniform))
		{
			throw "TriDObjectGLPass::Init() failed.";
			return false;
		}

		LPtr<GLUniform> viewMatrixUniform = new GLUniform("viewMatrix", GLUniform::TYPE_FLOAT_MAT4);
		auto viewMatrix = m_pMainCamera->GetViewportTransformMatrix();
		viewMatrixUniform->SetData(viewMatrix.GetData(), viewMatrix.GetDataSize());
		if (!m_pGLShaderProgram->AddUniform(viewMatrixUniform))
		{
			throw "TriDObjectGLPass::Init() failed.";
			return false;
		}

		LPtr<GLUniform> PerspectiveMatrixUniform = new GLUniform("projMatrix", GLUniform::TYPE_FLOAT_MAT4);
		auto projMatrix = m_pMainCamera->GetPerspectiveTransformMatrix();
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
		//m_pGLShaderProgram->SetGLUniformState();

		// Set light
		if (m_bOpenLight)
		{
			for (auto pLight : m_lights)
			{
				if (!pLight->SetLightUniformVar(program))
				{
					LeviathanOutStream << "[ERROR] Set light uniform var failed." << std::endl;
				}
			}
		}

		// Set viewMatrix
		_updateCameraMatrixUniform(program);

		// Render each GLObject
		for (auto& Object : m_GLObjects)
		{
			if (!Object->ApplyMaterial(program))
			{
				LeviathanOutStream << "[ERROR] Set material failed." << std::endl;
			}

			if (!Object->ApplyModelMatrix(m_pGLShaderProgram->GetUniformByName("modelMatrix")))
			{
				LeviathanOutStream << "[ERROR] Set model matrix failed." << std::endl;
			}

			m_pGLShaderProgram->SetGLUniformState();
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
		auto& pViewMatrixUniform = m_pGLShaderProgram->GetUniformByName("viewMatrix");
		if (!pViewMatrixUniform)
		{
			throw "TriDObjectGLPass::_updateCameraMatrixUniform(GLuint shaderProgram) --> GetUniform failed.";
			return;
		}

		auto viewMatrix = m_pMainCamera->GetViewportTransformMatrix();
		pViewMatrixUniform->SetData(viewMatrix.GetData(), viewMatrix.GetDataSize());

		auto& pPerspectiveMatrixUniform = m_pGLShaderProgram->GetUniformByName("projMatrix");
		if (!pPerspectiveMatrixUniform)
		{
			throw "TriDObjectGLPass::_updateCameraMatrixUniform(GLuint shaderProgram) --> GetUniform failed.";
			return;
		}

		auto PerspectiveMatrix = m_pMainCamera->GetPerspectiveTransformMatrix();
		pPerspectiveMatrixUniform->SetData(PerspectiveMatrix.GetData(), PerspectiveMatrix.GetDataSize());
	}
}