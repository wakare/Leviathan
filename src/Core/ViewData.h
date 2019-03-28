#pragma once
#include "LPtr.h"
#include "IScene.h"

namespace Leviathan
{
	class EventSystem;
	class CommonScene;
	class RenderWindow;

	class ViewData
	{
	public:
		ViewData(IScene::ESceneType type);

		EventSystem& GetEventSystem();
		RenderWindow& GetRenderWindow();
		CommonScene& GetScene();

	private:
		LPtr<EventSystem> m_pEventSystem;
		LPtr<RenderWindow> m_pRenderWindow;
		LPtr<CommonScene> m_pScene;
		IScene::ESceneType m_sceneType;
	};
}