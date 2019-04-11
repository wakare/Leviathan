#pragma once
#include <Eigen/Dense>
#include "IResource.h"

namespace Leviathan
{
	class Light : public IResource
	{
	public:
		Light(Eigen::Vector3f position, Eigen::Vector3f ambientColor, Eigen::Vector3f diffuseColor, Eigen::Vector3f specularColor);

		EResourceType Type() const;
		bool SetLightCoord(const Eigen::Vector3f& newCoord);

		Eigen::Vector3f m_lightCoordination;
		Eigen::Vector3f m_ambientColor;
		Eigen::Vector3f m_diffuseColor;
		Eigen::Vector3f m_specularColor;
	};
}