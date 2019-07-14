#pragma once

#include <memory>
#include "VFXSampleBaseViewerAPIDefine.h"

namespace Leviathan
{
	namespace Scene
	{
		class LevScene;
	}

	namespace Viewer
	{
		class LevViewer;
		
		class LEV_VFX_SAMPLE_BASE_VIEWER_API VFXSampleBaseViewer 
		{
		public:
			VFXSampleBaseViewer();

			LevViewer& GetViewer();
			const LevViewer& GetViewer() const;

			void Run();

		private:
			std::shared_ptr<LevViewer> m_viewer;
		};
	}

	
}