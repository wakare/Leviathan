#pragma once

#include "BaseMath.h"

namespace Leviathan
{
	class Light
	{
	public:
		Light(Vector3f position, Vector3f ambientColor, Vector3f diffuseColor, Vector3f specularColor);
		bool SetLightCoord(const Vector3f& newCoord);

		Vector3f m_lightCoordination;
		Vector3f m_ambientColor;
		Vector3f m_diffuseColor;
		Vector3f m_specularColor;
	};
}