#include "LevLight.h"

namespace Leviathan
{
	namespace Scene
	{
		LevLight::LevLight(LevLightType type, int scene_obj_type)
			: LevSceneObject(scene_obj_type)
			, m_type(type)
		{

		}

		LevLight::~LevLight()
		{
		}

		const Eigen::Vector3f & LevLight::LightCoordination() const
		{
			return m_lightCoordination;
		}

		void LevLight::LightCoordination(const Eigen::Vector3f& val)
		{
			m_lightCoordination = val;
		}

		const Eigen::Vector3f & LevLight::AmbientColor() const
		{
			return m_ambientColor;
		}

		void LevLight::AmbientColor(const Eigen::Vector3f & val)
		{ 
			m_ambientColor = val; 
		}
		const Eigen::Vector3f & LevLight::DiffuseColor() const
		{
			return m_diffuseColor;
		}

		void LevLight::DiffuseColor(const Eigen::Vector3f & val)
		{
			m_diffuseColor = val;
		}

		const Eigen::Vector3f & LevLight::SpecularColor() const
		{
			return m_specularColor;
		}

		void LevLight::SpecularColor(const Eigen::Vector3f & val)
		{
			m_specularColor = val;
		}
	}
}


