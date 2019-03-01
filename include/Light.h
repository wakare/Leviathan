#pragma once
#include <Eigen/Dense>

namespace Leviathan
{
	class Light
	{
	public:
		Light(Eigen::Vector3f position, Eigen::Vector3f ambientColor, Eigen::Vector3f diffuseColor, Eigen::Vector3f specularColor);
		bool SetLightCoord(const Eigen::Vector3f& newCoord);

		Eigen::Vector3f m_lightCoordination;
		Eigen::Vector3f m_ambientColor;
		Eigen::Vector3f m_diffuseColor;
		Eigen::Vector3f m_specularColor;
	};
}