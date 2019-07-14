#include "LevLight.h"

namespace Leviathan
{
	namespace Scene
	{
		LevLight::LevLight(LevLightType type, int scene_obj_type)
			: LevSceneObject(scene_obj_type | ELSOT_LIGHT)
			, m_lightType(type)
		{

		}

		LevLight::~LevLight()
		{
		}

		Leviathan::Scene::LevLightType LevLight::GetLightType() const
		{
			return m_lightType;
		}

		const Eigen::Vector3f & LevLight::AmbientColor() const
		{
			return m_ambientColor;
		}

		void LevLight::SetAmbientColor(const Eigen::Vector3f & val)
		{ 
			m_ambientColor = val; 
		}

		const Eigen::Vector3f & LevLight::DiffuseColor() const
		{
			return m_diffuseColor;
		}

		void LevLight::SetDiffuseColor(const Eigen::Vector3f & val)
		{
			m_diffuseColor = val;
		}

		const Eigen::Vector3f & LevLight::SpecularColor() const
		{
			return m_specularColor;
		}

		void LevLight::SetSpecularColor(const Eigen::Vector3f & val)
		{
			m_specularColor = val;
		}
	}
}


