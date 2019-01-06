#include "Light.h"

namespace Leviathan
{
	Light::Light(Vector3f position, Vector3f ambientColor, Vector3f diffuseColor, Vector3f specularColor):
		m_lightCoordination(position),
		m_ambientColor(ambientColor),
		m_diffuseColor(diffuseColor),
		m_specularColor(specularColor)
	{

	}

	bool Light::SetLightCoord(const Vector3f& newCoord)
	{
		m_lightCoordination = newCoord;

		return true;
	}

}