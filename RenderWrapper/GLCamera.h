#pragma once
#include "VectorOperation.h"
#include <memory>
#include <iostream>

struct Vector4f;

struct Matrix4f
{
public:
	friend Vector4f;

	Matrix4f(float* data) { memcpy(m_data, data, sizeof(float) * 16); }
	Matrix4f(const Matrix4f& ref) { memcpy(m_data, ref.m_data, sizeof(float) * 16); }
	Matrix4f& operator=(const Matrix4f& ref) { memcpy(m_data, ref.m_data, sizeof(float) * 16); }
	Matrix4f operator*(const Matrix4f& ref)
	{
		float result[4][4];
		for (unsigned i = 0; i < 4; i++)
		{
			for (unsigned j = 0; j < 4; j++)
			{
				result[i][j] =
					m_data[i][0] * ref.m_data[0][j] +
					m_data[i][1] * ref.m_data[1][j] +
					m_data[i][2] * ref.m_data[2][j] +
					m_data[i][3] * ref.m_data[3][j];
			}
		}

		return Matrix4f(reinterpret_cast<float*>(result));
	}

	float* GetData() { return reinterpret_cast<float*>(m_data); };
	unsigned GetDataSize() { return sizeof(float) * 16; }

private:
	float m_data[4][4];
}; 

struct Vector4f
{
public:
	Vector4f(float* data) { memcpy(m_data, data, sizeof(m_data)); }
	float* GetData() { return m_data; }
	unsigned GetDataSize() { return 4; }

	Vector4f operator*(const Matrix4f& ref)
	{
		float result[4];
		for (unsigned i = 0; i < 4; i++)
		{
			result[i] = 
				m_data[0] * ref.m_data[0][i] + 
				m_data[1] * ref.m_data[1][i] + 
				m_data[2] * ref.m_data[2][i] + 
				m_data[3] * ref.m_data[3][i];
		}

		return Vector4f(result);
	}

private:
	float m_data[4];
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

	void Rotate(float x, float y, float z)
	{
		float sinValue[3] = { sinf(x), sinf(y), sinf(z) };
		float cosValue[3] = { cosf(x), cosf(y), cosf(z) };
	
		// Rotate along X axis
		float XRotate[4][4] =
		{
			1.0f,			0.0f,			0.0f,				0.0f,
			0.0f,			cosValue[0],	-sinValue[0],		0.0f,
			0.0f,			sinValue[0],	cosValue[0],		0.0f,
			0.0f,			0.0f,			0.0f,				1.0f,
		};

		// Rotate along Y axis
		float YRotate[4][4] =
		{
			cosValue[1],	0.0f,			sinValue[1],		0.0f,
			0.0f,			1.0f,			0.0f,				0.0f,
			-sinValue[1],	0.0f,			cosValue[1],		0.0f,
			0.0f,			0.0f,			0.0f,				1.0f,
		};

		// Rotate along Z axis
		float ZRotate[4][4] =
		{
			cosValue[2],	-sinValue[2],	0.0f,				0.0f,
			sinValue[2],	cosValue[2],	0.0f,				0.0f,
			0.0f,			0.0f,			1.0f,				0.0f,
			0.0f,			0.0f,			0.0f,				1.0f,
		};

		Matrix4f xMatrix(reinterpret_cast<float*>(XRotate));
		Matrix4f yMatrix(reinterpret_cast<float*>(YRotate));
		Matrix4f zMatrix(reinterpret_cast<float*>(ZRotate));
	
		Matrix4f rotateMatrix = xMatrix * yMatrix * zMatrix;

		static auto _updateCameraAttribute = [&](float* attribute)
		{
			float attributeArray[4] = { attribute[0], attribute[1], attribute[2], 1.0f };
			Vector4f attributeVector = Vector4f(attributeArray) * rotateMatrix;

			memcpy(attributeArray, attributeVector.GetData(), sizeof(attributeArray));
			if (fabs(attributeArray[3]) < FLT_EPSILON)
			{
				throw "Error attribute array.";
			}

			attributeArray[0] /= attributeArray[3];
			attributeArray[1] /= attributeArray[3];
			attributeArray[2] /= attributeArray[3];

			memcpy(attribute, attributeArray, 3 * sizeof(float));
		};

		_updateCameraAttribute(m_fEye);
		_updateCameraAttribute(m_fLookAt);
		_updateCameraAttribute(m_fUp);
	}

	float m_fEye[3];
	float m_fLookAt[3];
	float m_fUp[3]; 

	float m_fovy;
	float m_fAspect;
	float m_fZNear;
	float m_fZFar;
};