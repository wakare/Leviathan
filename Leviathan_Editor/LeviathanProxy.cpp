#include "LeviathanProxy.h"
#include "LevScene.h"
#include "ILevWindow.h"

LeviathanProxy::LeviathanProxy()
	: m_viewer(new Viewer::LevViewer())
	, m_state(EPS_UNINITED)
{
}

bool LeviathanProxy::_initScene()
{
	m_main_scene.Reset(new Scene::LevScene());
 	EXIT_IF_FALSE(m_main_scene->Init(ELST_3D_SCENE));
	m_viewer->SetCurrentScene(m_main_scene);

	return true;
}

bool LeviathanProxy::Init(unsigned width, unsigned height, unsigned handle)
{
	m_viewer->CreateRenderWindow(width, height, handle);
	EXIT_IF_FALSE(_initScene());

	m_state = EPS_INITED;
	return true;
}

bool LeviathanProxy::HasInited() const
{
	return m_state > EPS_UNINITED;
}

void LeviathanProxy::Stop()
{
	m_viewer->SetStop();
}

bool LeviathanProxy::HasStoped() const
{
	return m_viewer->HasStoped();
}

void LeviathanProxy::Update()
{
	if (m_state < EPS_INITED || m_state > EPS_RUNNING)
	{
		return;
	}

	m_viewer->TickFrame();
	m_state = EPS_RUNNING;
}

unsigned LeviathanProxy::GetWindowHandle() const
{
	return m_viewer->GetRenderWindow().GetWindowHandle();
}
