#pragma once
#include "VFXCommonScene.h"

namespace Leviathan
{
	namespace Viewer
	{
		class VFXMeshTestScene : public VFXCommonScene
		{
		public:
			VFXMeshTestScene();

		private:
			void _createMeshTestScene();
		};
	}
}