#include "LevUISystem.h"
#include "LevSceneData.h"
#include "LevCamera.h"

namespace Leviathan
{
	namespace UI
	{
		LevUISystem::LevUISystem()
			: m_ui_scene(new LevScene)
		{
			auto main_camera = m_ui_scene->GetSceneData().GetMainCamera();
			main_camera->SetReceiveInput(false);

			m_root_ui_rect = new UIRect;
			m_root_ui_rect->x = 0;
			m_root_ui_rect->y = 0;
			m_root_ui_rect->width = 1280;
			m_root_ui_rect->height = 720;
		}

		void LevUISystem::AddUIRect(unsigned ui_layer_index, LSPtr<UIRect> ui_rect)
		{
			m_ui_rects[ui_layer_index] = ui_rect;
		}

		void LevUISystem::_setupUItoUIScene()
		{
			m_ui_scene->GetSceneData().
		}
	}
}