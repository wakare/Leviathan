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
	m_nPolygonMode = GL_LINE;
	glPolygonMode(GL_FRONT_AND_BACK, m_nPolygonMode);
	auto program = m_pGLShaderProgram->GetShaderProgram();

	glUseProgram(program);

	for (auto& Object : m_GLObjects)
	{
		auto VAO = Object->GetVAO();
		if (VAO == 0)
		{
			return;
		}
		glBindVertexArray(VAO);
		glDrawArrays(Object->GetPrimType(), 0, Object->GetVertexCount());
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

	glUseProgram(0);

	// Call PostCallBack
	for (auto& process : m_PostRenderCallBacks)
	{
		process();
	}
}
