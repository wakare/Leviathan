#pragma once

#include <memory>
#include "VFXSampleBaseViewerAPIDefine.h"

namespace Leviathan
{
	namespace Viewer
	{
		class LevViewer;

		class LEV_VFX_SAMPLE_BASE_VIEWER_API VFXSampleBaseViewer 
		{
		public:
			VFXSampleBaseViewer();

			void Run();

		private:
			std::shared_ptr<LevViewer> m_viewer;
		};
	}

	
}