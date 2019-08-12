#pragma once
#include "LevSceneRenderAttribute.h"
#include "LPtr.h"
#include <map>

namespace Leviathan
{
	namespace Scene
	{
		class ILevRAttrUniform;

		class LEV_SCENE_API LevRAttrUniformManager : public LevSceneRenderAttribute
		{
		public:
			LevRAttrUniformManager();

			void AddUniform(LPtr<ILevRAttrUniform> uniform);
			const std::map<std::string, LPtr<ILevRAttrUniform>>& GetUniforms() const;

		private:
			std::map<std::string, LPtr<ILevRAttrUniform>> m_uniforms;
		};
	}
}