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

			ADD_RENDER_ATTRIBUTE_IMPLEMENT(LevRAttrUniformManager);

			RenderAttributeType GetRenderAttributeType() const override { return ERAT_UNIFORM_MANAGER; }

			void AddUniform(LSPtr<ILevUniform> uniform);
			const std::map<std::string, LSPtr<ILevUniform>>& GetUniforms() const;

		private:
			std::map<std::string, LSPtr<ILevUniform>> m_uniforms;
		};
	}
}