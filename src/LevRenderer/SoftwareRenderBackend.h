#pragma once

#include "IRendererBackend.h"
namespace Leviathan
{
	namespace Renderer
	{
		class SoftwareRenderBackend : public IRendererBackend
		{
		public:
			bool SetInputData(const Scene::LevSceneData& data) override;
			void Update() override;
		};
	}
}

