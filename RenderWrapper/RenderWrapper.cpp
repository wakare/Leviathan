#include "RenderWrapper.h"

void RenderWrapper::Render()
{
	if (!m_pWindow)
	{
		throw "Render window is invalid";
		return;
	}

	// Set Global state
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Render subProcess
	/*for (int nIndex = 0; nIndex < RenderSubProcessLevelCount; nIndex++)
	{
		RenderSubProcessLevel currentLevel = static_cast<RenderSubProcessLevel>(nIndex);
		for (auto subProcess : m_subProcessVec)
		{
			if (subProcess.first == currentLevel)
				subProcess.second->Render();
		}
	}*/

	glfwSwapBuffers(m_pWindow);
}
