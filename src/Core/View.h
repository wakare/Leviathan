#pragma once

#include <memory>
#include "GlobalDef.h"
#include "LPtr.h"
#include "ViewData.h"

class AABB;

namespace Leviathan
{
	class EventListener;
	
	namespace Scene
	{
		class LevSceneData;
	}

	class View
	{
	public:
		View(LevSceneType type = ELST_3D_SCENE);

		bool Init(int width, int height, int handle);
		void Update();
		void SyncStop();
		void AsyncStop();

		bool AddEventListener(EventType eventType, LPtr<EventListener> listener);

		int GetWindowHandle() const;
		Scene::LevSceneData& GetSceneData();

		bool LoadMesh(const char* file, bool bResetCamera = true);
		bool LoadPointCloud(const char* file, bool bResetCamera = true);

	private:
		void _resetCamera(const AABB& aabb);

		std::unique_ptr<ViewData> m_pData;
	};
}