#include "Light.h"

namespace Leviathan
{
	Light::Light(Eigen::Vector3f position, Eigen::Vector3f ambientColor, Eigen::Vector3f diffuseColor, Eigen::Vector3f specularColor):
		m_lightCoordination(position),
		m_ambientColor(ambientColor),
		m_diffuseColor(diffuseColor),
		m_specularColor(specularColor)
	{

	}

	bool Light::SetLightCoord(const Eigen::Vector3f& newCoord)
	{
		m_lightCoordination = newCoord;
		return true;
	}

}