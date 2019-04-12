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
	
	class ViewData
	{
	public:
		ViewData(LevRendererType render_type);
		EventSystem& GetEventSystem();
		LevRenderWindow& GetRenderWindow();
		Scene::LevScene& GetScene();
		Renderer::IRenderer& GetRenderer();
		bool InitRenderer();

	private:
		LevRendererType m_renderType;
		LPtr<EventSystem> m_pEventSystem;
		LPtr<LevRenderWindow> m_pWindow;
		LPtr<Scene::LevScene> m_pScene;
		LPtr<Renderer::IRenderer> m_pRenderer;
	};

}