#pragma once

#include <string>
#include <Eigen/Dense>

namespace Leviathan
{
	class Material
	{
	public:
		Material(const Eigen::Vector3f& ambient, const Eigen::Vector3f& diffuse, const Eigen::Vector3f& specular, float fShininess, std::string textureName) :
			m_ambient(ambient),
			m_diffuse(diffuse),
			m_specular(specular),
			m_fShininess(fShininess),
			m_textureName(textureName)
		{

		}

		Eigen::Vector3f m_ambient;
		Eigen::Vector3f m_diffuse;
		Eigen::Vector3f m_specular;
		float m_fShininess;
		std::string m_textureName;
	};
}