#pragma once
#include "LevViewer.h"
#include "ThreadRecorder.h"
#include <functional>
#include <mutex>
#include <vector>

using namespace Leviathan;

enum ProxyState
{
	EPS_UNINITED,
	EPS_INITED,
	EPS_RUNNING,
	EPS_STOP,
};

typedef std::function<void(Scene::LevScene& scene)> SceneDataUpdateRequest;

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
	void UpdateSceneData(SceneDataUpdateRequest updater);

private:
	bool _initScene();
	void _processDataUpdateRequest();

	ProxyState m_state;
	LSPtr<Scene::LevScene> m_main_scene;
	LSPtr<Viewer::LevViewer> m_viewer;

	std::mutex m_scene_data_request_mutex;
	std::vector<SceneDataUpdateRequest> m_scene_update_request;
};