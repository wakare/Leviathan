#pragma once

#include <string>
#include "BaseMath.h"

class Material
{
public:
	Material(const Vector3f& ambient, const Vector3f& diffuse, const Vector3f& specular, float fShininess, std::string textureName):
		m_ambient(ambient),
		m_diffuse(diffuse),
		m_specular(specular),
		m_fShininess(fShininess),
		m_textureName(textureName)
	{

	}

	Vector3f m_ambient;
	Vector3f m_diffuse;
	Vector3f m_specular;
	float m_fShininess;
	std::string m_textureName;
};