#include "RenderWrapper.h"
#include <Algorithm>

void RenderWrapper::PreInit()
{
	m_bPreInited = true;
}

void RenderWrapper::Render()
{
	if (!m_bPreInited)
	{
		PreInit();
	}

	if (!m_pWindow)
	{
		throw "RenderWrapper::Render() --> Render window is invalid";
		return;
	}

	// Set Global state
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Render subProcess
	for (auto& pGLPass : m_GLPasses)
	{
		if (!pGLPass->Init())
		{
			throw "RenderWrapper::Render() --> GLPass Init failed.";
			return;
		}

		pGLPass->Render();
	}

	//glUseProgram(shaderProgram);
	//glBindVertexArray(VAO);
	////glDrawArrays(GL_TRIANGLES, 0, 6);
	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	//glBindVertexArray(0);
	
	glfwSwapBuffers(m_pWindow);
}

bool RenderWrapper::AddGLPass(std::shared_ptr<GLPass> _GLPass)
{
	auto findResult = std::find(m_GLPasses.begin(), m_GLPasses.end(), _GLPass);
	if (findResult != m_GLPasses.end())
	{
		return false;
	}

	m_GLPasses.push_back(_GLPass);
	return true;
}

bool RenderWrapper::DelGLPass(std::shared_ptr<GLPass> _GLPass)
{
	auto findResult = std::find(m_GLPasses.begin(), m_GLPasses.end(), _GLPass);
	if (findResult == m_GLPasses.end())
	{
		return false;
	}

	m_GLPasses.erase(findResult);
	return true;
}
