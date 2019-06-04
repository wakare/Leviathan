#pragma once
#include "LevViewer.h"
#include "ThreadRecorder.h"

using namespace Leviathan;

enum ProxyState
{
	EPS_UNINITED,
	EPS_INITED,
	EPS_RUNNING,
	EPS_STOP,
};

class LeviathanProxy : public ThreadRecorder
{
public:
	LeviathanProxy();
	
	bool Init(unsigned width, unsigned height, unsigned handle);
	bool HasInited() const;
	void Stop();
	bool HasStoped() const;
	void Update();

	unsigned GetWindowHandle() const;
	Scene::LevScene& GetScene();
	const Scene::LevScene& GetScene() const;

private:
	bool _initScene();

	ProxyState m_state;
	LPtr<Scene::LevScene> m_main_scene;
	LPtr<Viewer::LevViewer> m_viewer;
};