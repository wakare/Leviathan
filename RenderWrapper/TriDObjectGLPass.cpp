#include "TriDObjectGLPass.h"
#define EXIT_GET_FALSE(statement) { if (!statement) return false;}

bool TriDObjectGLPass::Init()
{
	if (m_bInited)
	{
		return true;
	}

	EXIT_GET_FALSE(m_pGLShaderProgram);
	EXIT_GET_FALSE(m_pGLShaderProgram->Init());

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
	glPolygonMode(GL_FRONT_AND_BACK, m_nPolygonMode);
	
	// Set GLProgram
	auto program = m_pGLShaderProgram->GetShaderProgram();
	glUseProgram(program);
	m_pGLShaderProgram->SetGLUniformState();

	// Render each GLObject
	for (auto& Object : m_GLObjects)
	{
		Object->Render(program);
	}

	// ResetProgram
	glUseProgram(0);

	// Call PostCallBack
	for (auto& process : m_PostRenderCallBacks)
	{
		process();
	}
}
