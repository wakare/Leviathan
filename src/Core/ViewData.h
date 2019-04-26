#pragma once
#include "LPtr.h"

namespace Leviathan
{
	namespace Renderer
	{
		class IRenderer;
	}

	namespace Scene
	{
		class LevScene;
	}

	class LevRenderWindow;
	class EventSystem;
	class LevWindowFactory;
	class ILevWindow;

	class ViewData
	{
	public:
		ViewData(LevRendererType render_type);
		EventSystem& GetEventSystem();
		ILevWindow& GetRenderWindow();
		Scene::LevScene& GetScene();
		Renderer::IRenderer& GetRenderer();
		bool InitRenderer();

	private:
		LevRendererType m_renderType;
		LPtr<LevWindowFactory> m_pLevWindowFactory;
		LPtr<EventSystem> m_pEventSystem;
		//LPtr<LevRenderWindow> m_pWindow;
		LPtr<ILevWindow> m_pWindow;
		LPtr<Scene::LevScene> m_pScene;
		LPtr<Renderer::IRenderer> m_pRenderer;
	};

}