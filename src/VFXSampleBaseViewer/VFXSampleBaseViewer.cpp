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
		}

		Leviathan::Viewer::LevViewer& VFXSampleBaseViewer::GetViewer()
		{
			return *m_viewer;
		}

		const Leviathan::Viewer::LevViewer& VFXSampleBaseViewer::GetViewer() const
		{
			return *m_viewer;
		}

		void VFXSampleBaseViewer::Run()
		{
			if (!m_viewer->HasAttachedScene())
			{
				LPtr<Scene::LevScene> scene = new VFXCommonScene;
				m_viewer->SetCurrentScene(scene);
			}

			while (true)
			{
				m_viewer->TickFrame();
			}
		}
	}
}



