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
		class LevSceneNode;
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
		LPtr<Scene::LevSceneNode> LoadPointCloud(const char* file, bool bResetCamera = true);
		void RemoveAllRenderables(bool bSync = false);

	private:
		void _resetCamera(const AABB& aabb);

		std::unique_ptr<ViewData> m_pData;
	};
}