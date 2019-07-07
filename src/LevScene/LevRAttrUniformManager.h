#pragma once
#include "LevSceneRenderAttribute.h"
#include "LPtr.h"
#include <map>

namespace Leviathan
{
	namespace Scene
	{
		class LevRAttrUniform;

		class LEV_SCENE_API LevRAttrUniformManager : public LevSceneRenderAttribute
		{
		public:
			LevRAttrUniformManager();

			void AddUniform(LPtr<LevRAttrUniform> uniform);
			const std::map<std::string, LPtr<LevRAttrUniform>>& GetUniforms() const;

		private:
			std::map<std::string, LPtr<LevRAttrUniform>> m_uniforms;
		};
	}
}