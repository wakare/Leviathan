#pragma once
#include "VectorOperation.h"
#include <memory>

struct Matrix4f
{
public:
	Matrix4f(float* data) { memcpy(m_data, data, sizeof(float) * 16); }
	Matrix4f(const Matrix4f& ref) { memcpy(m_data, ref.m_data, sizeof(float) * 16); }
	Matrix4f& operator=(const Matrix4f& ref) { memcpy(m_data, ref.m_data, sizeof(float) * 16); }
	
	float* GetData() { return m_data; };
	unsigned GetDataSize() { return sizeof(float) * 16; }

private:
	float m_data[16];
};

class GLCamera 
{
public:
	GLCamera(float* eye, float* lookAt, float* up, float fovy, float aspect, float zNear, float zFar):
		m_fovy(fovy), 
		m_aspect(aspect), 
		m_zNear(zNear), 
		m_zFar(zFar)
	{
		memcpy(m_eye, eye, sizeof(float) * 3);
		memcpy(m_lookAt, lookAt, sizeof(float) * 3);
		memcpy(m_up, up, sizeof(float) * 3);
	};

	Matrix4f GetViewportTransformMatrix()
	{
		float N[3] = 
		{
			m_eye[0] - m_lookAt[0],
			m_eye[1] - m_lookAt[1],
			m_eye[2] - m_lookAt[2],
		};

		Normalize<float, 3>(N);

		float U[3];
		Vec3Cross(m_up, N, U, true);

		float V[3];
		Vec3Cross(N, U, V, true);

		float data[16] =
		{
			U[0], U[1], U[2], VecDot<float, 3>(U, m_eye),
			V[0], V[1], V[2], VecDot<float, 3>(V, m_eye),
			N[0], N[1], N[2], VecDot<float, 3>(N, m_eye),
			0.0f, 0.0f, 0.0f,						 1.0f,
		};

		Matrix4f result = Matrix4f(data);
		return result;
	};

	Matrix4f GetPerspectiveTransformMatrix()
	{
		float tanHalfFovy = tanf(m_fovy / 2.0f);

		float data[16] =
		{
			1.0f / (m_aspect * tanHalfFovy), 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f / tanHalfFovy , 0.0f, 0.0f,
			0.0f, 0.0f, (-m_zNear - m_zFar) / (m_zNear - m_zFar) , 2 * m_zFar * m_zNear / (m_zNear - m_zFar),
			0.0f, 0.0f, 1.0f, 0.0f
		};

		Matrix4f result = Matrix4f(data);
		return result;
	};

	float m_eye[3];
	float m_lookAt[3];
	float m_up[3]; 

	float m_fovy;
	float m_aspect;
	float m_zNear;
	float m_zFar;
};