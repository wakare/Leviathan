#pragma once
#include <memory>

class GLCamera 
{
public:
	GLCamera(float* eye, float* look, float* up, float fovy, float aspect, float zNear, float zFar):
		m_fovy(fovy), m_aspect(aspect), m_zNear(zNear), m_zFar(zFar)
	{
		memcpy(m_eye, eye, sizeof(float) * 3);
		memcpy(m_look, look, sizeof(float) * 3);
		memcpy(m_up, up, sizeof(float) * 3);
	};

	float m_eye[3];
	float m_look[3];
	float m_up[3]; 

	float m_fovy;
	float m_aspect;
	float m_zNear;
	float m_zFar;
};