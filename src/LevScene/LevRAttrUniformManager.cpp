#include "LevRAttrUniformManager.h"
#include "LevRAttrUniform.h"

namespace Leviathan
{
	namespace Scene
	{
		LevRAttrUniformManager::LevRAttrUniformManager()
			: LevSceneObjectAttribute(ELSOAT_RENDER)
		{
		}

		void LevRAttrUniformManager::AddUniform(LPtr<LevRAttrUniform> uniform)
		{
			m_uniforms[uniform->GetName()] = uniform;
		}


		const std::map<std::string, Leviathan::LPtr<Leviathan::Scene::LevRAttrUniform>>& LevRAttrUniformManager::GetUniforms() const
		{
			return m_uniforms;
		}

	}
}