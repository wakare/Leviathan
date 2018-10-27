#pragma once
#include "VectorOperation.h"
#include <memory>
#include <iostream>

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
		m_fAspect(aspect), 
		m_fZNear(zNear), 
		m_fZFar(zFar)
	{
		memcpy(m_fEye, eye, sizeof(float) * 3);
		memcpy(m_fLookAt, lookAt, sizeof(float) * 3);
		memcpy(m_fUp, up, sizeof(float) * 3);
	};

	Matrix4f GetViewportTransformMatrix()
	{
		float N[3] = 
		{
			m_fEye[0] - m_fLookAt[0],
			m_fEye[1] - m_fLookAt[1],
			m_fEye[2] - m_fLookAt[2],
		};

		Normalize<float, 3>(N);

		float U[3];
		Vec3Cross(m_fUp, N, U, true);

		float V[3];
		Vec3Cross(N, U, V, true);

		// Debug
		//std::cout << "m_camera:" << m_fEye[0] << " " << m_fEye[1] << " " << m_fEye[2] << std::endl;
		
		float data[16] =
		{
			U[0], U[1], U[2], VecDot<float, 3>(U, m_fEye),
			V[0], V[1], V[2], VecDot<float, 3>(V, m_fEye),
			N[0], N[1], N[2], VecDot<float, 3>(N, m_fEye),
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
			1.0f / (m_fAspect * tanHalfFovy), 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f / tanHalfFovy , 0.0f, 0.0f,
			0.0f, 0.0f, (-m_fZNear - m_fZFar) / (m_fZNear - m_fZFar) , 2 * m_fZFar * m_fZNear / (m_fZNear - m_fZFar),
			0.0f, 0.0f, 1.0f, 0.0f
		};

		Matrix4f result = Matrix4f(data);
		return result;
	};

	void Translate(float x, float y, float z)
	{
		std::cout << "GLCamera::position " << m_fEye[0] << " " << m_fEye[1] << "" << m_fEye[2] << std::endl;

		float N[3] =
		{
			m_fEye[0] - m_fLookAt[0],
			m_fEye[1] - m_fLookAt[1],
			m_fEye[2] - m_fLookAt[2],
		};

		Normalize<float, 3>(N);

		float U[3];
		Vec3Cross(m_fUp, N, U, true);

		float V[3];
		Vec3Cross(N, U, V, true);

		m_fEye[0] += (x * U[0] + y * V[0] + z * N[0]);
		m_fEye[1] += (x * U[1] + y * V[1] + z * N[1]);
		m_fEye[2] += (x * U[2] + y * V[2] + z * N[2]);
	}

	void Rotate()
	{

	}

	float m_fEye[3];
	float m_fLookAt[3];
	float m_fUp[3]; 

	float m_fovy;
	float m_fAspect;
	float m_fZNear;
	float m_fZFar;
};