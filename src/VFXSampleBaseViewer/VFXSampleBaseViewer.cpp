#include "VFXSampleBaseViewer.h"
#include "VFXCommonScene.h"
#include "LevViewer.h"
#include "LevScene.h"

namespace Leviathan
{
	namespace Viewer
	{
		VFXSampleBaseViewer::VFXSampleBaseViewer()
			: m_viewer(new LevViewer())
		{
			auto created = m_viewer->CreateRenderWindow(800, 600, 0);
			LEV_ASSERT(created);

			LPtr<Scene::LevScene> scene = new VFXCommonScene;
			m_viewer->SetCurrentScene(scene);
		}

		void VFXSampleBaseViewer::Run()
		{
			while (true)
			{
				m_viewer->TickFrame();
			}
		}
	}
}



