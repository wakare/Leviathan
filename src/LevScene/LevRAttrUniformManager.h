#pragma once
#include "LevSceneRenderAttribute.h"
#include "LPtr.h"
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

			void AddUniform(LPtr<ILevUniform> uniform);
			const std::map<std::string, LPtr<ILevUniform>>& GetUniforms() const;

		private:
			std::map<std::string, LPtr<ILevUniform>> m_uniforms;
		};
	}
}