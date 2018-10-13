#pragma once
#include <memory>

struct Matrix4f
{
	Matrix4f(float* data) { memcpy(m_data, data, sizeof(float) * 16); }
	float* GetData() { return m_data; };

	float m_data[16];
};

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

	Matrix4f GetViewportTransformMatrix()
	{

	};

	Matrix4f GetPerspectiveTransformMatrix()
	{

	};

	float m_eye[3];
	float m_look[3];
	float m_up[3]; 

	float m_fovy;
	float m_aspect;
	float m_zNear;
	float m_zFar;
};