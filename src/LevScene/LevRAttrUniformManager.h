#pragma once
#include "LevSceneRenderAttribute.h"
#include "LSPtr.h"
#include <map>

namespace Leviathan
{
	namespace Scene
	{
		class ILevUniform;

		class LEV_SCENE_API LevRAttrUniformManager : public LevSceneRenderAttribute
		{
		public:
			LevRAttrUniformManager();

			void AddUniform(LSPtr<ILevUniform> uniform);
			const std::map<std::string, LSPtr<ILevUniform>>& GetUniforms() const;

		private:
			std::map<std::string, LSPtr<ILevUniform>> m_uniforms;
		};
	}
}