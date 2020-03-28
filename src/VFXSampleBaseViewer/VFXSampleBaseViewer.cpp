#include "VFXSampleBaseViewer.h"
#include "VFXCommonScene.h"
#include "LevViewer.h"
#include "LevScene.h"
#include "VFXDeferRenderScene.h"
#include "VFXSDFScene.h"
#include "VFXShadowMapScene.h"
#include "VFXSkyboxScene.h"
#include "VFXMeshTestScene.h"
#include "VFXFireParticleScene.h"

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
				//LSPtr<Scene::LevScene> scene = new VFXDeferRenderScene;
				//LSPtr<Scene::LevScene> scene = new VFXSDFScene;
				//LSPtr<Scene::LevScene> scene = new VFXShadowMapScene;
				LSPtr<Scene::LevScene> scene = new VFXSkyBoxScene;
				//LSPtr<Scene::LevScene> scene = new VFXMeshTestScene;
				//LSPtr<Scene::LevScene> scene = new VFXFireParticleScene;
				m_viewer->SetCurrentScene(scene);
			}

			while (!m_viewer->HasStoped())
			{
				m_viewer->TickFrame();
			}
		}
	}
}



